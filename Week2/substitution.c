#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

string encrypt(string key,string plaintext);

int main(int argc,string argv[])
{

    //只能有一个命令行参数，否则报错并返回1
    if(argc != 2)
    {
        printf("Error: Usage: ./substitution key\n\n");
        return 1;
    }
    //检测命令行参数是否为26个字母
    else if(strlen(argv[1]) != 26)
    {
        printf("Error: key must be 26 alphabetic characters.\n");
        return 1;
    }
    //字母是否无重复（不区分大小写）
    else
    {
        string key = argv[1];
        //一个判断是否重复的好思路
        bool seen[26] = {false};
        int index[26];
        for(int i = 0;i < 26;i++)
        {
            if(!isalpha(key[i])){
                printf("Error: Key must only contain alphabetic characters.\n\n");
                return 1;
            }
            else{
                index[i] = toupper(key[i]) - 'A';
                if(seen[index[i]]){
                    printf("Error: Key must not contain repeated letters.\n\n");
                    return 1;
                }
                else{
                    seen[index[i]] = true;
                }
            }
        }
    }
    //对输入的文本进行一一转化
    string plaintext = get_string("Text: ");
    string ciphertext = encrypt(argv[1],plaintext);
    printf("ciphertext: %s\n",ciphertext);
}

string encrypt(string key,string plaintext)
{
    string ciphertext = plaintext;//相当于为ctext分配空间，值得注意
    int index;
    for(int i = 0;i < strlen(plaintext);i++){
        if(isalpha(plaintext[i])){
            //避免冗余的ifelse判断
            index = isupper(plaintext[i]) ? plaintext[i] - 'A' : plaintext[i] - 'a';
            ciphertext[i] = isupper(plaintext[i]) ? toupper(key[index]) : tolower(key[index]);
        }else{
            ciphertext[i] = plaintext[i];
        }
    }
    return ciphertext;
}
