# pipex

## Overview
I have reimplemented the shell's pipe, heredoc, and append redirection.

## Requirement
macOS

## Usage
``` bash
  git clone ...
  cd pipex
```
### Mandatory part
  ``` bash
  make
  ./pipex file1 cmd1 cmd2 file2
  ```
  example:
  
    ./pipex infile "ls -l" "wc -l" outfile
    (pipex behaves like: < infile ls -l | wc -l > outfile)

### Bonus part
  ``` bash
  make bonus
  ./pipex_bonus here_doc LIMITER cmd1 cmd2 file1
  ```
  example:

    ./pipex_bonus here_doc LIMITER "wc -l" cat outfile
    (pipex behaves like: wc -l << LIMITER | cat >> file)
