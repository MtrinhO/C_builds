#include <stdio.h>

int main(void)
{
    //Input float cc number
    long cc = get_long("Enter CC number: ");

    //Negative number filter
    if(cc<0)
    {
        printf("INVALID\n");
    }

    //Form array to store digits
    int cc_digits[16];
    long denom1 = 1;
    for (int i=0; i<16; i++)
    {
        long divisor1 = cc/denom1;
        cc_digits[i] = divisor1%10;
        denom1 = denom1*10;

        //STOP for shorter cc numbers
        if(divisor1<1)
        {
          cc_digits[i]=-1;
          continue;
        }

    }
    //Luhnd's Algorithm (1): nth and n+2th digits

    int n1_digits[8];
    long denom_n1=1;
    for (int b=0; b<8; b++)
    {
        long divisor_n1 = cc/denom_n1;
        n1_digits[b] = divisor_n1%10;
        denom_n1=denom_n1*100;

     //STOP for shorter cc numbers
        if(divisor_n1<1)
        {
          n1_digits[b]=-1;
          continue;
        }
    }

    int n2_digits[8];
    long denom_n2=10;
    for (int m=0; m<8; m++)
    {
        long divisor_n2 = cc/denom_n2;
        n2_digits[m] = divisor_n2%10;
        denom_n2=denom_n2*100;

    //STOP for shorter cc numbers
        if(divisor_n2<1)
        {
          n2_digits[m]=-1;
          continue;
        }
    }

    //Lundh's Algorithm (2a): Multiplying all n+2th digits by two, adding digits to checksum.
   int checksum=0;
   for (int x=0; x<8; x++)
   {
       n2_digits[x]= 2*n2_digits[x];

       //Check for products over 10, continue into digits
       if(n2_digits[x]>9)
       {
           checksum += n2_digits[x]%10;
           checksum += (n2_digits[x]/10)%10;
       }

       //Do not add any negative placeholder digits
       else if(n2_digits[x]<0)
       {
           continue;
       }

       else
       {
           checksum += n2_digits[x];
       }
   }
   //Lundh's Algorithm (2b): Adding all nth digits to checksum
   for (int y=0; y<8; y++)
   {
       //Do not add any negative placeholder digits
       if(n1_digits[y]<0)
       {
           continue;
       }
       else
       {
           checksum += n1_digits[y];
       }
   }

   //Lundh's Algorithm (3): Checking checksum

   bool validity;
   if(checksum%10==0)
   {
       validity=true;
   }
   else
   {
       validity=false;
       printf("INVALID\n");
   }

   //Credit card holder identifier

   if(validity==true && cc_digits[15]==-1 && cc_digits[14]==3 && (cc_digits[13]==4 || cc_digits[13]==7))
   {
       printf("AMEX\n");
   }
   else if(validity==true && cc_digits[15]==5 && (cc_digits[14]==1 || cc_digits[14]==2 || cc_digits[14]==3 || cc_digits[14]==4 || cc_digits[14]==5))
   {
       printf("MASTERCARD\n");
   }
   else if(validity==true && (cc_digits[15]==4 || (cc_digits[12]==4 && cc_digits[15]==-1 && cc_digits[14]==-1 && cc_digits[13]==-1)))
   {
       printf("VISA\n");
   }
   else
   {
       printf("INVALID\n");
   }
}