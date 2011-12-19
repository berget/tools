# Simple Module to Send Mail via Python

## Description

send email simply, support attachments, unicode and /usr/sbin/sendmail(8).

Released under MIT license.

Thanks to Ryan Ginstrom for his/her work: http://ginstrom.com/code/mailer.html and 
Python email module document: http://docs.python.org/library/email-examples.html

## Features

* support both smtp directly and /usr/sbin/sendmail(8)
* support attachments
* support unicode
* support html
* support default sender(user@hostname)

## Example

0. startup sendmail if required

`sudo /etc/init.d/sendmail start`
or
`sudo service sendmail start`

1. basic

```python
msg = Message(recp = ['foo@bar.com'], subject='hello', text='world')
mailer = Mailer()
mailer.send(msg)
```

2. send html mail

```python
msg = Message(recp = ['foo@bar.com'], subject='hello', html='<html><body>world</body></html>') 
mailer = Mailer()
mailer.send(msg)
```

3. attachments

```python
msg = Message(recp = ['foo@bar.com'], subject='hello', text='world', attachments=['/etc/foobar']) 
mailer = Mailer()
mailer.send(msg)
```

4. importance(high or low)

```python
msg = Message(recp = ['foo@bar.com'], subject='hello', text='world', importance='high') 
mailer = Mailer()
mailer.send(msg)
```


## TODO

* support stmp login
