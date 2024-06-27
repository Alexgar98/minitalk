# minitalk
minitalk is a simple project that requires to program a server which will receive signals and translate them to a message, and a client that will send the codified message. Only two signals, SIGUSR0 and SIGUSR1, may be used, which forces to convert all messages to binary. You can find the subject <a href="https://github.com/rphlr/42-Subjects/blob/main/common-core/minitalk/en.subject.pdf">here</a>.
This project was validated on 29th May 2024.

<h3>Things to improve:</h3>
The server might not work as intended when multiple clients are running at the same time. I did not take that into account, nor did my evaluators.
