package main

func (c *Client) handleUpdate() {
	var messages []*Message
	for _, msg := range c.maildrop.messages {
		if !msg.Delete {
			messages = append(messages, msg)
		}
	}

	c.maildrop.messages = messages

	if len(c.maildrop.messages) == 0 {
		c.OK("POP3 server signing off (maildrop empty)")
	} else {
		c.OK("POP3 server signing off (%d messages left)", len(c.maildrop.messages))
	}

	c.maildrop.lock = false

	c.conn.Close()
}
