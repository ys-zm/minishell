
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
