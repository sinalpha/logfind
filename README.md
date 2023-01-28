# logfind

Linux program for searching keywords form files   

Usage:     
    
>./logfind (keyword) (keyword) [-o: AND option]    
>__Program requires .logfind file__  

Example usage:    
    
__./logfind hello__, It will print files including "hello".    
__./logfind hello my -o__, It will ptrit files includg "hello" and "my"

Example .logfind:

![image](https://user-images.githubusercontent.com/59336397/215263143-3a707ad4-755c-4781-85fd-841935f59a2e.png)

Architecture:   

<p align="center"><img src="src/architechure.png" width="500px" height="1000px" ></img><br/></p>
