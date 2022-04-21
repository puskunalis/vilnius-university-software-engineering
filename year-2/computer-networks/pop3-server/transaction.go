package main

import (
	"bufio"
	"fmt"
	"regexp"
	"strconv"
	"strings"

	"github.com/mitchellh/hashstructure"
)

func (c *Client) handleTransaction() {
	messages, size := c.maildrop.info()
	c.OK("%s's maildrop has %d messages (%d octets)", c.name, messages, size)

	reader := bufio.NewReader(c.conn)

	for {
		msg, err := reader.ReadString('\r')
		if err != nil {
			fmt.Printf("Connection closed on %s\n", c.conn.RemoteAddr())
			c.maildrop.lock = false
			c.conn.Close()
			return
		}

		cmd, arg1, arg2 := parseMessage(msg)

		switch cmd {
		// Custom command
		case "REGX":
			re, err := regexp.Compile(arg1)
			if err != nil {
				c.ERR("invalid regular expression")
				continue
			}

			var matchedMessages []int
			var size int

			for i, msg := range c.maildrop.messages {
				if !msg.Delete && re.MatchString(msg.Body) {
					matchedMessages = append(matchedMessages, i+1)
					size += len(msg.Body)
				}
			}

			c.OK("%d messages (%d octets)", len(matchedMessages), size)

			for _, msg := range matchedMessages {
				c.Send("%d %d", msg, len(c.maildrop.messages[msg-1].Body))
			}
			c.Send(".")
		case "STAT":
			messages, size := c.maildrop.info()
			c.OK("%d %d", messages, size)
		case "LIST":
			if arg1 == "" {
				messages, size := c.maildrop.info()
				c.OK("%d messages (%d octets)", messages, size)

				for i, msg := range c.maildrop.messages {
					if !msg.Delete {
						c.Send("%d %d", i+1, len(msg.Body))
					}
				}
				c.Send(".")
			} else {
				msgID, err := strconv.Atoi(arg1)
				if err != nil || msgID < 1 {
					c.ERR("enter a positive number")
					continue
				}

				if msgID > len(c.maildrop.messages) {
					c.ERR("no such message, %d messages in maildrop", len(c.maildrop.messages))
					continue
				}

				msg := c.maildrop.messages[msgID-1]

				if msg.Delete {
					c.ERR("message %d is deleted", msgID)
					continue
				}

				c.OK("%d %d", msgID, len(msg.Body))
			}
		case "RETR":
			msgID, err := strconv.Atoi(arg1)
			if err != nil || msgID < 1 {
				c.ERR("enter a positive number")
				continue
			}

			if msgID > len(c.maildrop.messages) {
				c.ERR("no such message, %d messages in maildrop", len(c.maildrop.messages))
				continue
			}

			msg := c.maildrop.messages[msgID-1]

			if msg.Delete {
				c.ERR("message %d is deleted", msgID)
				continue
			}

			c.OK("%d octets", len(msg.Body))
			c.Send(msg.Body)
			c.Send(".")
		case "DELE":
			msgID, err := strconv.Atoi(arg1)
			if err != nil || msgID < 1 {
				c.ERR("enter a positive number")
				continue
			}

			if msgID > len(c.maildrop.messages) {
				c.ERR("no such message, %d messages in maildrop", len(c.maildrop.messages))
				continue
			}

			msg := c.maildrop.messages[msgID-1]
			if msg.Delete {
				c.ERR("message %d already deleted", msgID)
				continue
			}

			msg.Delete = true
			c.OK("message deleted")
		case "NOOP":
			c.OK()
		case "RSET":
			for _, msg := range c.maildrop.messages {
				msg.Delete = false
			}

			messages, size := c.maildrop.info()
			c.OK("maildrop has %d messages (%d octets)", messages, size)
		case "QUIT":
			c.handleUpdate()
			return
		case "TOP":
			msgID, err := strconv.Atoi(arg1)
			if err != nil || msgID < 1 {
				c.ERR("enter two positive numbers")
				continue
			}

			n, err := strconv.Atoi(arg2)
			if err != nil || msgID < 1 {
				c.ERR("enter two positive numbers")
				continue
			}

			if msgID > len(c.maildrop.messages) {
				c.ERR("no such message, %d messages in maildrop", len(c.maildrop.messages))
				continue
			}

			msg := c.maildrop.messages[msgID-1]

			if msg.Delete {
				c.ERR("message %d is deleted", msgID)
				continue
			}

			c.OK()
			for k, v := range msg.Headers {
				c.Send("%s: %s", k, v)
			}
			c.Send()

			lines := strings.Split(msg.Body, "\r\n")
			for i := 0; i < n && i < len(lines); i++ {
				c.Send(lines[i])
			}
			c.Send(".")
		case "UIDL":
			if arg1 == "" {
				c.OK()

				for i, msg := range c.maildrop.messages {
					if !msg.Delete {
						hash, err := hashstructure.Hash(msg, &hashstructure.HashOptions{})
						if err != nil {
							panic(err)
						}

						c.Send("%d %d", i+1, hash)
					}
				}

				c.Send(".")
			} else {
				msgID, err := strconv.Atoi(arg1)
				if err != nil || msgID < 1 {
					c.ERR("enter a positive number")
					continue
				}

				if msgID > len(c.maildrop.messages) {
					c.ERR("no such message, %d messages in maildrop", len(c.maildrop.messages))
					continue
				}

				msg := c.maildrop.messages[msgID-1]

				if msg.Delete {
					c.ERR("message %d is deleted", msgID)
					continue
				}

				hash, err := hashstructure.Hash(*msg, &hashstructure.HashOptions{})
				if err != nil {
					panic(err)
				}

				c.OK("%d %d", msgID, hash)
			}
		default:
			c.ERR("unknown command")
		}
	}
}
