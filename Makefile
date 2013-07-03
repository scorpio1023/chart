all:recver sender
recver:recver.c
	gcc -g recver.c -o recver
sender:sender.c
	gcc -g sender.c -o sender
