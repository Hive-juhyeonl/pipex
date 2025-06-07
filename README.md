# Pipex

A C program that replicates a simple shell pipeline: it reads from an input file, passes data through two commands, and writes the result to an output file.

## Features
- Redirect `infile` to the first command’s stdin  
- Pipe first command’s stdout into the second command’s stdin  
- Redirect second command’s stdout to `outfile`  
- Handle errors (file access, command not found, etc.)

## Usage
```sh
./pipex infile "cmd1 [args…]" "cmd2 [args…]" outfile
```
infile: file to read input from

cmd1, cmd2: commands to execute (with optional arguments)

outfile: file to write the final output to

## How It Works
Open infile for reading and outfile for writing (create/truncate).

Create a pipe with pipe().

Fork first child:

Redirect its stdin to infile.

Redirect its stdout to the pipe’s write end.

Execute cmd1 with execve().

Fork second child:

Redirect its stdin to the pipe’s read end.

Redirect its stdout to outfile.

Execute cmd2 with execve().

Parent closes unused descriptors and waits for both children.
