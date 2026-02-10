// Unpacking Final Code 

import java.io.*;
import java.util.*;

class Unpacker
{
    public static void main(String A[]) throws Exception
    { 
        // Variable creation 
        int Filesize = 0;
        int i = 0;
        int iRet = 0;

        Scanner sobj = null;
        String FileName = null;
        String Header = null;
        String Tokens[] = null;

        
        File fpackobj = null;
        File fobj = null;

        FileInputStream fiobj = null;
        FileOutputStream foobj = null;

        byte bHeader[] = new byte[100];
        byte Buffer[] = null;
        byte Key = 0x11;

        sobj = new Scanner(System.in);

        System.out.println("Enter the name of Packed File");
        FileName = sobj.nextLine();

        fpackobj = new File(FileName);

        if(fpackobj.exists() == false)    // Or if(! fpackobj.exists())
        {
            System.out.println("Error : There is no such packed file");
            return;
        }

        fiobj = new FileInputStream(fpackobj);

        // Read the Header
        while ((iRet = fiobj.read(bHeader,0,100)) != -1) 
        {
            Header = new String(bHeader);

            Header = Header.trim();

            Tokens = Header.split(" ");

            System.out.println("File name : "+Tokens[0]);
            System.out.println("File size : "+Tokens[1]);

            fobj = new File(Tokens[0]);

            fobj.createNewFile();

            foobj = new FileOutputStream(fobj);

            Filesize = Integer.parseInt(Tokens[1]);

            Buffer = new byte[Filesize];

            // Read from packed file
            fiobj.read(Buffer,0,Filesize);

            // Decrypt the data
            for(i = 0; i < Filesize; i++)
            {
                Buffer[i] = (byte)(Buffer[i] ^ Key);
            }

            // Writo into extracted file
            foobj.write(Buffer,0,Filesize);

        }        
    }
}      
