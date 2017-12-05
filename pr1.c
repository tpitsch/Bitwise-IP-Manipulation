/*
Tyler Pitsch
CSE 333 C

IN addition to the assignemnt requirements I also added a 3rd option for the user to select 
which allows them to enter any positive decimal and a mask value.  The program will then 
convert that information into the host and prefix and display the decimal, binary, and dot decimal 
for the ip, mask, host, and prefix.
*/

#include <stdio.h>
#include <math.h>

//forward declarations of methods
unsigned int createMask(int subnet);
unsigned int toDecimal(int ip1,int ip2,int ip3,int ip4);
unsigned int createPrefix(unsigned int ip, unsigned int mask);
unsigned int createHost(unsigned int ip, unsigned int mask);
unsigned int getInput();


int main(){
   int convType;//first option, holds the decision of the user
   char repeat;//hold the choice to repeat or not
   //do while loop to control the repetetion of the conversions
   do{
      printf("Which conversion would you like to do?\n");
      printf("Please enter 1 for IP-adress and subnet, or 2 for host and network prefix\n");
      printf("or 3 for decimal ip and subnet: ");
      scanf(" %d",&convType);
      //will loop while the user doesn't give a good input of 1 or 2
      while(convType != 1 && convType != 2 && convType != 3){
         while(getchar() != '\n');//clears the buffer for really nasty inputs
	    printf("You made an invalid choice, please choose 1 or 2 or 3: ");
	    scanf(" %d", &convType);
      }
      //dertermis which conversion to do based on the users choice
      if(convType == 1) {
         optionOne();		
      }else if(convType == 2){
         optionTwo();
      }else{
	 optionThree();
      }
      
      printf("\nEnter r if you would like to do this again or q to exit: ");
      scanf(" %c",&repeat);
      //loops while the user doesnt make a good choice or r for repeat or q to quit
      while(repeat != 'r' && repeat != 'q'){
         while(getchar() != '\n');
         printf("\nYou entered a bad option, please enter r or q: ");
         scanf(" %c", &repeat);
         getchar();
      }
   }while(repeat != 'q');//lowercse q is the only valid quit option, runs until that happens
}

/*
This function executes the first conversion option.  Prompts the user for the ip and for 
the subnet.  Will then convert that ip into decimal form and use the ip to process output
for the mask, prefix, and host.
*/

int optionOne() {
   int ip1;int ip2;int ip3;int ip4;int subnet;

   printf("\nEnter the IP adress: ");
   //scanf grabs the desired decimal number while get char tosses the decimals an /
   scanf(" %d",&ip1);
   getchar();
   scanf(" %d",&ip2);
   getchar();
   scanf(" %d",&ip3);
   getchar();
   scanf(" %d",&ip4);
   getchar();
   scanf(" %d",&subnet);
   getchar();

   //confitrms that all values inbetween the dots are between 0 and 255 inclusive, also
   //makes sure that the subnet is between 0 and 32 inclusive.
   while(ip1 <0 || ip1 > 255 || ip2 <0 || ip2 > 255 || ip3 <0 || ip3 > 255
   || ip4 <0 || ip4 > 255 || subnet < 0 || subnet > 32){
      while(getchar() != '\n');
      printf("\nYou entered a bad IP adress, please try again: ");
      scanf(" %d",&ip1);
      getchar();
      scanf(" %d",&ip2);
      getchar();
      scanf(" %d",&ip3);
      getchar();
      scanf(" %d",&ip4);
      getchar();
      scanf(" %d",&subnet);
      getchar();
   }
   //all following code is to display all the information
   unsigned int decimal = toDecimal(ip1,ip2,ip3,ip4);
   printf("\nThe IP in decimal form is %u", decimal);

   printf("\n");
   toBinary(decimal);
   printf("\n");

   printf("\n");

   unsigned int mask = createMask(subnet);
   printf("The submask in decimal is %u", mask);
   printf("\n");
   toBinary(mask);

   printf("\n");
   toDotDecimal(mask);
   printf("\n");

   unsigned int prefix = createPrefix(decimal, mask);
   printf("\nThe prefix in decimal is %u",prefix);

   printf("\n");
   toBinary(prefix);
   printf("\n");

   toDotDecimal(prefix);
   printf("\n");
   printf("\n");

   unsigned int host = createHost(decimal, mask);
   printf("The Host ID in decimal:%u",host);

   printf("\n");
   toBinary(host);
   printf("\n");

   toDotDecimal(host);
}

/*
Controls the conversions of the second option.  Grabs input the same as the first option 
execpt it doesnt require a subnet because it calculates that itself.
*/

int optionTwo(){

   printf("\nEnter the host: ");
   unsigned int host = getInput();
   printf("\nEnter the prefix: ");
   unsigned int prefix = getInput();

   unsigned int ip = host | prefix;
   printf("\n");
   toDotDecimal(ip);
   //starts at least significent bit and looks for the first 1 to calculate the mask
   int subnet = 0;
   int i;
   for(i = 0; i <= 31;i++){
      if((prefix >> i) & 1){
         subnet = 32-i;
         break;
      }
   }
   printf("/%d",subnet);
}

int optionThree(){

   unsigned int ip;
   int subnet;
   
   printf("\nEnter the decimal representation of the ip with the mask: ");
   scanf(" %u",&ip);
   getchar();
   scanf(" %d", &subnet);
   while(ip < 0 || subnet <0 || subnet > 32){
      while(getchar() != '\n');
      printf("\nYou entered a bad number try again: ");
      scanf(" %u",&ip);
      getchar();
      scanf(" %d", &subnet);
   }
   toBinary(ip);
   printf("\n");
   
   printf("\n");
   unsigned int mask = createMask(subnet);
   printf("The submask in decimal is %u", mask);
   printf("\n");
   toBinary(mask);

   printf("\n");
   toDotDecimal(mask);
   printf("\n");

   unsigned int prefix = createPrefix(ip, mask);
   printf("\nThe prefix in decimal is %u",prefix);

   printf("\n");
   toBinary(prefix);
   printf("\n");

   toDotDecimal(prefix);
   printf("\n");
   printf("\n");

   unsigned int host = createHost(ip, mask);
   printf("The Host ID in decimal:%u",host);

   printf("\n");
   toBinary(host);
   printf("\n");

   toDotDecimal(host);
   



}

/*
Grabs input for the second option.  It requires two dot decimal adresses but no subnet.
*/
unsigned int getInput(){

   int ip1;int ip2;int ip3;int ip4;

   scanf(" %d",&ip1);
   getchar();
   scanf(" %d",&ip2);
   getchar();
   scanf(" %d",&ip3);
   getchar();
   scanf(" %d",&ip4);
   getchar();

   while(ip1 <0 || ip1 > 255 || ip2 <0 || ip2 > 255 || ip3 <0 || ip3 > 255
   || ip4 <0 || ip4 > 255){
      while(getchar() != '\n');
      printf("\nYou entered a bad adress, please try again: ");
      scanf(" %d",&ip1);
      getchar();
      scanf(" %d",&ip2);
      getchar();
      scanf(" %d",&ip3);
      getchar();
      scanf(" %d",&ip4);
      getchar();
   }

   return toDecimal(ip1,ip2,ip3,ip4);



}
//converts each piece of the 4 part dot decimal into a sing 32 bit number
unsigned int toDecimal(int ip1,int ip2,int ip3,int ip4){

   unsigned int total;

   total = (ip1*pow(256,3));	
   total += (ip2*pow(256,2));
   total += (ip3*256);
   total += ip4;

   return total;


}

/*Parses the enire 32 bit unsigned int looking at each bit to determine if it should
print a 1 or a 0
*/
int toBinary(unsigned int num){

   int i;
   int b;
   printf("In binary: ");
   //runs through the bits from left to right to ensure the bits are printed correctly
   for(i = 31;i>=0;i--){
      if((i+1) % 8 == 0){
         printf(" ");
      }
      if((b = num>>i) & 1){		
         printf("1");
      }else {
         printf("0");
      }
   }

}

/*
Creates the subnet mask by bit shifting from left to right adding a 1 along the way
*/
unsigned int createMask(int subnet){

   unsigned int mask = 0;

   int i;
   for(i=31;i>=32-subnet;i--){
      mask = mask | (1<<i);//by using the bitwise or and comparing it to one each bit becomes 1
   }
	
   return mask;
}

/*
Calculates the dot decimal representation of the number one byte at a time
*/
int toDotDecimal(unsigned int num){

   int i;
   int j;
   int c = 0;
   int total = 0;
   //grabs bits in sets of 8 then moves 1 by 1 though the byte to calculate a running total
   printf("In dot-decimal: ");
   for(i = 31;i > 0;i-=8){
      for(j = 7;j>=0;j--){
         if((num >> i-c) & 1){
            total += pow(2,j);
         }
         c++;
      }
      c=0;
      printf("%d",total);
      total = 0;
      if(i != 7){
         printf(".");
      }
   }
}

//creates the prefix of the two given numbers
unsigned int createPrefix(unsigned int ip, unsigned int mask){

   unsigned int prefix;
   prefix = ip & mask;

   return prefix;

}

//creates the host for the two given numbers
unsigned int createHost(unsigned int ip, unsigned int mask){

   unsigned int host;
   unsigned int maskComp = ~mask;
   host = ip & maskComp;

   return host;

}







