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
  ./pipex infile cmd1 cmd2 outfile
  ```
  examples:
  
    ./pipex infile "ls -l" "wc -l" outfile
    pipex behaves like: < infile ls -l | wc -l > outfile

### Bonus part
  ``` bash
  .pipex_bonus
## Features

## Reference

## Author

[twitter](https://twitter.com/Kotabrog)

## Licence

[MIT](https://......)
