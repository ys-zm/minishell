
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
// echo "\\s" and echo "\s" should both ==> \s | only \\\ or \\\\ show two and so forth
//env
//env weirddddd ==> no such file or directory

//export
//export var=a - export $var=test - echo $var $a !!!!
//export $variouh=test outputinBASH: bash: export: `=test': not a valid identifier
//export $var=test - unset var
//export "" test=a

//"" - should give the output of error/ command not found not permission denied

//ls | exit ==>shouldnt print exit on command line

//exit
//should decrement shlvl


//cat<>out --> shoudl create outfile!
//echo $ | echo $$$ --- prints 8010...wtf
//SEG FAULTS!
//error when you ctrl D in a heredoc
//echo 'ab"cd'ef'gh"ij'kl --> SEGFAULT FUCK
//echo " hello '$USER' world " !
//<< heredocs in general, not working
