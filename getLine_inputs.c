#include "shell.h"

#include "shell.h"

/**
 * deep_cover - buffers covert operations
 * @data: secret agent struct
 * @buf: covert buffer address
 * @len: undercover length
 *
 * Return: hidden data size
 */
ssize_t deep_cover(data_d *data, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t secret_len = 0;

	if (!*len) /* If nothing remains in the cover, refill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, stealthHandler);
#if USE_GETLINE
		x = getline(buf, &secret_len, stdin);
#else
		x = _getline(data, buf, &secret_len);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0'; /* Remove trailing newline */
				x--;
			}
			data->hidden_count_flag = 1;
			remove_comments(*buf);
			build_hidden_history(data, *buf, data->secret_count++);
			{
				*len = x;
				data->covert_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * undercover_communication - gets a secret message without the newline
 * @data: secret agent struct
 *
 * Return: hidden data size
 */
ssize_t undercover_communication(data_d *data)
{
	static char *buf; /* The ';' covert operation buffer */
	static size_t a, b, secret_length;
	ssize_t x = 0;
	char **buf_agent = &(data->agent_arg), *p;

	_putchar(BUF_FLUSH);
	x = deep_cover(data, &buf, &secret_length);
	if (x == -1) /* EOF */
		return (-1);
	if (secret_length) /* There are messages left in the covert buffer */
	{
		b = a; /* Initialize a new undercover agent to the current buffer position */
		p = buf + a; /* Get a pointer for the return */

		check_covert_operations(data, buf, &b, a, secret_length);
		while (b < secret_length) /* Iterate to semicolon or end */
		{
			if (is_covert(data, buf, &b))
				break;
			b++;
		}

		a = b + 1; /* Increment past nulled ';' */
		if (a >= secret_length) /* Reached the end of the buffer? */
		{
			a = secret_length = 0; /* Reset position and length */
			data->covert_buf_type = COVERT_NORM;
		}

		*buf_agent = p; /* Pass back a pointer to the current agent position */
		return (_strlen(p)); /* Return the length of the current agent's message */
	}

	*buf_agent = buf; /* Otherwise, not an agent, pass back the buffer from _getline() */
	return (x); /* Return the length of the buffer from _getline() */
}

/**
 * covert_read - reads covert data
 * @data: secret agent struct
 * @buf: covert buffer
 * @a: size

 *
 * Return: x
 */
ssize_t covert_read(data_d *data, char *buf, size_t *a)
{
	ssize_t x = 0;

	if (*a)
		return (0);
	x = read(data->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*a = x;
	return (x);
}

/**
 * _secret_message - gets the next message from STDIN
 * @data: secret agent struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _secret_message(data_d *data, char **ptr, size_t *length)
{
	static char secret_buf[READ_BUF_SIZE];
	static size_t a, secret_length;
	size_t b;
	ssize_t x = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == secret_length)
		a = secret_length = 0;

	x = covert_read(data, secret_buf, &secret_length);
	if (x == -1 || (x == 0 && secret_length == 0))
		return (-1);

	c = _strchr(secret_buf + a, '\n');
	b = c ? 1 + (unsigned int)(c - secret_buf) : secret_length;
	new_p = _realloc(p, s, s ? s + b : b + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, secret_buf + a, b - a);
	else
		_strncpy(new_p, secret_buf + a, b - a + 1);

	s += b - a;
	a = b;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * stealthHandler - prevents ctrl-C
 * @sig_num: signal number
 *
 * Return: void
 */
void stealthHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
