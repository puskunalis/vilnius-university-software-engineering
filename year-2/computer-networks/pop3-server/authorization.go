package main

import (
	"bufio"
	"fmt"
)

func (c *Client) handleAuthorization() {
	reader := bufio.NewReader(c.conn)

	for {
		msg, err := reader.ReadString('\r')
		if err != nil {
			fmt.Printf("Connection closed on %s\n", c.conn.RemoteAddr())
			c.conn.Close()
			return
		}

		cmd, arg1, arg2 := parseMessage(msg)

		switch cmd {
		case "USER":
			if !validateArgs(arg1) {
				c.ERR("invalid arguments")
				continue
			}

			if maildrop, ok := maildrops[arg1]; ok {
				c.name = arg1
				c.maildrop = maildrop
				c.OK("username ok")
			} else {
				c.ERR("user does not exist")
			}
		case "PASS":
			if !validateArgs(arg1) {
				c.ERR("invalid arguments")
				continue
			}

			if c.maildrop.lock {
				c.ERR("maildrop is locked")
				continue
			}

			if c.name != "" && c.maildrop.password == arg1 {
				c.maildrop.lock = true
				c.handleTransaction()
				return
			}

			c.ERR("permission denied")
		case "QUIT":
			c.OK("POP3 server signing off")
			fmt.Printf("Connection closed on %s\n", c.conn.RemoteAddr())
			c.conn.Close()
			return
		case "APOP":
			if !validateArgs(arg1, arg2) {
				c.ERR("invalid arguments")
				continue
			}

			maildrop, ok := maildrops[arg1]
			if !ok {
				c.ERR("maildrop not found")
				continue
			}

			if maildrop.lock {
				c.ERR("maildrop is locked")
				continue
			}

			digest := c.timestamp + maildrop.secret

			if encodeMD5(digest) == arg2 {
				c.maildrop = maildrop
				maildrop.lock = true
				c.handleTransaction()
				return
			}

			c.ERR("permission denied")
		default:
			c.ERR("unknown command")
		}
	}
}
