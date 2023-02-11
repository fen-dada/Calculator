#include "comp.h"

Comp stk_comp[100];
char stk_comp_op[100];
double stk_comp_int[100];
int top_comp=-1;
int top_comp_op=-1;
int top_comp_int=-1;
int prc[6]={0,1,1,2,2,3};

Comp add(Comp c1,Comp c2){
		Comp ans;
		ans.real=c1.real+c2.real;
		ans.imag=c1.imag+c2.imag;
	return ans;
}

Comp minus(Comp c1,Comp c2){
		Comp ans;
		ans.real=c1.real-c2.real;
		ans.imag=c1.imag-c2.imag;
	return ans;
}

Comp mul(Comp c1,Comp c2){
		Comp ans;
		ans.real=c1.real*c2.real;
		ans.real-=c1.imag*c2.imag;
		ans.imag=c1.real*c2.imag+c2.real*c1.imag;
	return ans;
}

Comp divi(Comp c1,Comp c2){

		double temp=pow(c2.real,2.0)+pow(c2.imag,2.0);
		c1.imag/=temp;
		c1.real/=temp;
		c2.imag=-c2.imag;
		return mul(c1,c2);
}





void calc_work()
{
	//printf("nmsl");
    Comp b=stk_comp[top_comp];
	top_comp--;
	Comp a;
    
				a=stk_comp[top_comp];
	      top_comp--;
		
    char op=stk_comp_op[top_comp_op];
	top_comp_op--;
    Comp ans;
    if(op=='+') ans=add(a,b);
    else if(op=='-') ans=minus(a,b);
    else if(op=='*') ans=mul(a,b);
    else if(op=='/') ans=divi(a,b);
		

    stk_comp[++top_comp]=ans;
//    for(int i=0;i<=top_int;i++) printf("%d ",stk_int[i]);
//    puts("");
//    for(int i=0;i<=top_op;i++) printf("%C ",stk_op[i]);
//    puts("");
    //printf("%d %d\n",a,b);
    return;
}


Comp comp_calc(const char str[]){

				for(int i=0;i<strlen(str);i++)
        {
        if(isdigit(str[i])){
            double x=0;
            while(i<strlen(str) && isdigit(str[i])){
                x=x*10+str[i++]-'0';
            }
            i--;
            //stk_comp_int[++top_comp_int]=x;
						Comp temp;
						temp.real=x;
						temp.imag=0;
						stk_comp[++top_comp]=temp;
        }
        else if(str[i]=='(') stk_comp_op[++top_comp_op]=str[i];
        else if(str[i]==')'){
            while(stk_comp_op[top_comp_op]!='(') calc_work();
            //printf("%d\n",stk_op[top_op]!='(');
            top_comp_op--;
        }
				else if(str[i]=='.'){
        	i++;
        	int n=-1;
        	
        	while(i<strlen(str) && isdigit(str[i])){
        		stk_comp_int[top_comp_int]+=pow(10,n)*(str[i++]-'0');
        		n--;
					}
					i--;
				}else if(str[i]=='i'){
							Comp temp;
						temp.imag=0;
					temp.real=0;
					if(top_comp>-1) temp = stk_comp[top_comp--];
							double a;
							if(isdigit(str[i-1])){
										a = temp.real;
										temp=stk_comp[top_comp--];
							}else{
									a=1.0;
							}
							
					    if(temp.imag!=0){
									stk_comp[++top_comp]=temp;
								Comp t;
								t.imag=a;
								stk_comp[++top_comp]=t;
							}else {
								  if(stk_comp_op[top_comp_op]=='-'){
											a=-a;
											top_comp_op--;
									}else if(stk_comp_op[top_comp_op]=='*'){
											a=temp.real;
											temp.real=0;
										top_comp_op--;
									}
									temp.imag=a;
								  stk_comp[++top_comp]=temp;
									
							}
							
							
							
							//stk_comp[++top_comp]=temp;
				}
        else{
            int top=0,cur=0;
            if(stk_comp_op[top_comp_op]=='+') top=1;
            else if(stk_comp_op[top_comp_op]=='-') top=2;
            else if(stk_comp_op[top_comp_op]=='*') top=3;
            else if(stk_comp_op[top_comp_op]=='/') top=4;
						
            if(str[i]=='+') cur=1;
            else if(str[i]=='-') cur=2;
            else if(str[i]=='*') cur=3;
            else if(str[i]=='/') cur=4;
						

					while(top_comp_op>-1 && prc[top]>=prc[cur] && str[i]!='^' && stk_comp_op[top_comp_op]!='('){
								calc_work();
							
							if(stk_comp_op[top_comp_op]=='+') top=1;
							else if(stk_comp_op[top_comp_op]=='-') top=2;
							else if(stk_comp_op[top_comp_op]=='*') top=3;
							else if(stk_comp_op[top_comp_op]=='/') top=4;
							
						}
							
            stk_comp_op[++top_comp_op]=str[i];
        }
    }
		
		
		while(top_comp_op!=-1) calc_work();
		
		/*
		while(top_comp_int!=-1){
				Comp temp = stk_comp[top_comp--];
				temp.real+=stk_comp_int[top_comp_int--];
			  stk_comp[++top_comp]=temp;
		}
		*/
		
    
   
    


    Comp ans = stk_comp[top_comp];
		top_comp--;
		top_comp_int=-1;
		top_comp_op=-1;
		memset(stk_comp,0,sizeof(stk_comp));
		memset(stk_comp_op,0,sizeof(stk_comp));
		memset(stk_comp_int,0,sizeof(stk_comp));
		return ans;
}







