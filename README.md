# dns_forwarder
`dns_forwarder` listens for DNS queries on UDP socket `127.0.0.1:9000`
and forwards them to a remote server address specified via command
line arguments. Replies from the remove server are forwarded back 
to the original requester.

<h3>Build</h3>

```
cd build
make
```

<h3>Run</h3>

```
cd build
./dns_forwarder remote_server_ip remote_server_port
Example: ./dns_forwarder 127.0.0.1 53
```

<h3>Clean</h3>

```
cd build
make clean
```
