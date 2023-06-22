
//tests for builtins
int main(void)
{
    // more than one '=' sign
    ft_export("aaa=aaa=aaa");

    // no equals sign
    ft_export("a");

    //double quotes
    ft_export("aaa""fd=faf");

    //closed single quotes should simply join contents between the quotes
    ft_export("a='a''b'c");
}


//Run these commands to compile for arch x86_64 in arm64
// arch -x86_64 /bin/bash
// arch -x86_64 /usr/local/bin/brew install llvm

//Errors:
// cat <Makefile exists the program completely

//Edge cases:
// echo:
// echo ~ ==> $HOME - should this happen in the expander or....
// echo "\\s" and echo "\s" should both ==> \s | only \\\ or \\\\ show two and so forth *maybe not important
//env
//env weirddddd ==> no such file or directory

//export
//export var=a - export $var=test - echo $var $a !!!!
//export $variouh=test outputinBASH: bash: export: `=test': not a valid identifier
//export $var=test - unset var
//export "" test=a //empty string does not work!! add to export cannot set empty string!, instead err msg: "bash: export: `': not a valid identifier"
 
//"" - should give the output of error/ command not found not permission denied --! do not pass to execve, handle before, command not found

//ls | exit ==>shouldnt print exit on command line

//exit
//should decrement shlvl


//cat<>out --> shoudl create outfile!
//echo $ | echo $$$ --- prints 8010...wtf
//SEG FAULTS!
//echo 'ab"cd'ef'gh"ij'kl --> SEGFAULT FUCK
//echo " hello '$USER' world " !
