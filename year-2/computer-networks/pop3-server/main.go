package main

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
	"net"
	"os"
	"strconv"
	"strings"
	"time"
)

type Message struct {
	Delete     bool
	Headers    map[string]string
	Body       string
	Attachment []byte
}

type Maildrop struct {
	lock     bool
	password string
	secret   string
	messages []*Message
}

type Client struct {
	name      string
	timestamp string
	maildrop  *Maildrop
	conn      net.Conn
}

const (
	Port              = 110
	Hostname          = "puskunalis.lt"
	ArgumentMaxLength = 40
)

var (
	maildrops = map[string]*Maildrop{
		"a": {password: "a123", secret: "a123secret", messages: []*Message{{Body: "a"}, {Body: "123"}}},
		"b": {password: "b123", secret: "bb123secret", messages: []*Message{{Body: "b"}, {Body: "b"}, {Body: "123123"}}},
		"c": {password: "c123", secret: "ccc123secret", messages: []*Message{
			{Body: ""},
			{Body: "c"},
			{Body: "cc"},
			{Body: "ccc"},
			{Body: "one"},
			{Body: "two"},
			{Body: "three"},
			{Body: "123asd123"},
			{Body: "+37061234567"},
			{Body: "+37069876543"},
			{Headers: map[string]string{"From": "A", "To": "C"}, Body: "123\r\n123\r\n123", Attachment: []byte("attachment")},
		}},
	}
)

func main() {
	ln, err := net.Listen("tcp", ":"+strconv.Itoa(Port))
	if err != nil {
		panic(err)
	}
	defer ln.Close()

	fmt.Printf("POP3 server is running at %s, port %d\n", Hostname, Port)

	for {
		conn, err := ln.Accept()
		if err != nil {
			fmt.Printf("error: %v\n", err)
		}

		timestamp := fmt.Sprintf("<%d.%d@%s>", os.Getpid(), time.Now().UnixMicro(), Hostname)
		c := &Client{conn: conn, timestamp: timestamp}
		fmt.Printf("New connection accepted from %s\n", c.conn.RemoteAddr())

		c.OK("POP3 server ready %s", timestamp)
		go c.handleAuthorization()
	}
}

func encodeMD5(text string) string {
	hash := md5.Sum([]byte(text))
	return hex.EncodeToString(hash[:])
}

func parseMessage(msg string) (cmd, arg1, arg2 string) {
	msg = strings.TrimSpace(msg)
	keywords := strings.Split(msg, " ")
	cmd, args := keywords[0], keywords[1:]

	if len(args) > 0 {
		arg1 = args[0]
		if len(args) > 1 {
			arg2 = args[1]
		}
	}

	return strings.ToUpper(cmd), arg1, arg2
}

func validateArgs(args ...string) bool {
	for _, arg := range args {
		if len(arg) > ArgumentMaxLength {
			return false
		}
	}
	return true
}

func (m *Maildrop) info() (messages, size int) {
	for _, msg := range m.messages {
		if !msg.Delete {
			messages++
			size += len(msg.Body)
		}
	}
	return
}

func (c *Client) Send(args ...any) {
	if len(args) == 0 {
		fmt.Fprintf(c.conn, "\r\n")
	} else {
		msg := fmt.Sprintf(args[0].(string), args[1:]...)
		fmt.Fprintf(c.conn, msg+"\r\n")
	}
}

func (c *Client) SendStatus(status string, args ...any) {
	if len(args) == 0 {
		c.Send(status)
	} else {
		msg := fmt.Sprintf(args[0].(string), args[1:]...)
		c.Send(status + " " + msg)
	}
}

func (c *Client) OK(args ...any) {
	c.SendStatus("+OK", args...)
}

func (c *Client) ERR(args ...any) {
	c.SendStatus("-ERR", args...)
}
