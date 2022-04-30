# banner.c
A program to display file content as a banner in a terminal, made in c.

## Compile:
```
gcc banner.c -o banner -DTOTAL=total
```
where ```total``` is an unsigned integer containing the number of columns the program should be displayed in. If ```TOTAL``` is not provided on compile time, then a default value will be used.

### Note:
Never provide ```total``` a value that is greater than the total columns in a terminal. Else the banner would not remain like banner.
