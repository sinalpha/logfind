# logfind

Linux program for searching keywords form files   

Usage:     
    
>./logfind (keyword) (keyword) [-o: AND option]    
>__Program requires .logfind file__  

Way of writing .logfind file:
>*.(file extension)   
>(one of the file names)

Example usage:    
    
__./logfind hello__, It will print files including "hello".    
__./logfind hello my -o__, It will ptrit files includg "hello" and "my"

Example .logfind:

<p align="center"> <img src="https://user-images.githubusercontent.com/59336397/215263176-8e097865-902f-4aaf-8c39-e61e6dd38bc3.png"> </p>


Architecture:   

<p align="center"><img src="src/architechure.png" width="500px" height="1000px" ></img><br/></p>
