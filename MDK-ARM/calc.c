#include"calc.h"
//char str[200];
double stk_int[100];
char stk_op[100];
int top_int=-1;
int top_op=-1;
bool legal=true;
int pr[7]={0,1,1,2,2,3,1};

double fact(double x){
		if(x==1) return 1;
		else if(x<1) return 1;
		else{
			return x*fact(x-1);
		}
}


void work()
{
    double b=stk_int[top_int];
	top_int--;
    double a=0;
	
    char op=stk_op[top_op];
	top_op--;
	if(is_op(op)){
			a=stk_int[top_int];
	    top_int--;
	}
    double ans;
    if(op=='+') ans=a+b;
    else if(op=='-') ans=a-b;
    else if(op=='*') ans=a*b;
    else if(op=='/'){
				 ans=a/b;
			if(b==0) legal=false;
		}
		else if(op=='s') ans=sin(b);
	  else if(op=='c') ans=cos(b);
	  else if(op=='t') ans=tan(b);
		else if(op=='l'){
				 ans=log(b);
			if(b<=0){
					legal=false;
			}
		}
		else if(op=='i'){
				ans=asin(b);
				if(b>1 || b<-1){
						legal=false;
				}
		} 
		else if(op=='o'){
				ans=acos(b);
			if(b>1 || b<-1){
						legal=false;
				}
		} 
		else if(op=='p') ans=atan(b);
		else if(op=='!') ans=fact(b);
		else{
			ans=pow((double)a,(double)b);
	}
		stk_int[++top_int]=ans;
    return;
}

bool is_op(char op){
    if(op=='+'||op=='-'||op=='*'||op=='/'||op=='^') return true;
    else return false;
}

void strinst(char* str,int idx,char c){
	for(int i=strlen(str);i>idx;i--){
		str[i]=str[i-1];
	}
	//len++;
	str[idx]=c;
}

double calc(char str[]){
    //scanf("%s",str);
    //gets(str);
    //printf("%c",str[1]);


    int sum=0;

    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]=='(') sum++;
        if(str[i]==')') sum--;
        if(sum<0){
            legal=false;
            break;
        }
        
    }
		/*
		for(int i=0;i<strlen(str);i++){
    	if(str[i]=='-'&&!isdigit(str[i-1])){
        	strinst(str,i,'0');
        	i++;
        	//printf("%s\n",str);
		}
	}
		*/

    for(int i=1;i<strlen(str);i++){
        if(
            //( is_op(str[i]) && is_op(str[i-1]) ) || 
            //( is_op(str[i]) && str[i-1] == '(' ) || //(-
            ( is_op(str[i-1]) && str[i] == ')' ) ||
            ( str[i] == '(' && isdigit(str[i-1]) ) ||
            ( isdigit(str[i]) && str[i-1] == ')') ||
						(is_op(str[strlen(str)-1])) ||
						(is_op(str[0])) ||
						(str[i-1]=='/' && str[i]=='0')
        ){
            legal=false;
            break;
        }
    }

    if(sum||!legal||(strlen(str) == 2 && is_op(str[0])))
    {
        //printf("no");
        //to judge it's right
				legal=false;
				return 0;
    }

    for(int i=0;i<strlen(str);i++)
    {
        if(isdigit(str[i])){
            double x=0;
            while(i<strlen(str) && isdigit(str[i])){
                x=x*10+str[i++]-'0';
            }
            i--;
            stk_int[++top_int]=x;
        }
        else if(str[i]=='(') stk_op[++top_op]=str[i];
        else if(str[i]==')'){
            while(stk_op[top_op]!='(') work();
            //printf("%d\n",stk_op[top_op]!='(');
            top_op--;
        }
				else if(str[i]=='.'){
        	i++;
        	int n=-1;
        	
        	while(i<strlen(str) && isdigit(str[i])){
        		stk_int[top_int]+=pow(10,n)*(str[i++]-'0');
        		n--;
					}
					i--;
				}else if(str[i]=='s'){
						i+=2;
						stk_op[++top_op]='s';
				}else if(str[i]=='c'){
						i+=2;
						stk_op[++top_op]='c';
				}else if(str[i]=='t'){
						i+=2;
					  stk_int[++top_op]='t';
				}else if(str[i]=='l'){
						if(str[i+1]=='n'){
								i++;
								stk_op[++top_op]='l';
						}else{
							i+=2;
								stk_op[++top_op]='g';
						}
				}else if(str[i]=='e'){
							stk_int[++top_int]=2.7182818285;
				}else if(str[i]=='p'){
						i++;
							stk_int[++top_int]=3.14159265358979;
				}else if(str[i]=='a'){
						if(str[i+3]=='s'){
								i+=5;
								stk_op[++top_op]='i';
						}else if(str[i+3]=='c'){
								i+=5;
								stk_op[++top_op]='o';
						}else if(str[i+3]=='t'){
								i+=5;
								stk_op[++top_op]='p';
						}
				}else if(str[i]=='!'){
						stk_op[++top_op]='!';
				}
        else{
            int top=0,cur=0;
            if(stk_op[top_op]=='+') top=1;
            else if(stk_op[top_op]=='-') top=2;
            else if(stk_op[top_op]=='*') top=3;
            else if(stk_op[top_op]=='/') top=4;
						else if(stk_op[top_op]=='^') top=5;
						else if(stk_op[top_op]=='s') top=6;

            if(str[i]=='+') cur=1;
            else if(str[i]=='-') cur=2;
            else if(str[i]=='*') cur=3;
            else if(str[i]=='/') cur=4;
						else if(str[i]=='^') cur=5;
						else if(str[i]=='s') cur=6;

					while(top_op>-1 && pr[top]>=pr[cur] && str[i]!='^' && stk_op[top_op]!='('){
								work();
							
							if(stk_op[top_op]=='+') top=1;
							else if(stk_op[top_op]=='-') top=2;
							else if(stk_op[top_op]=='*') top=3;
							else if(stk_op[top_op]=='/') top=4;
							else if(stk_op[top_op]=='^') top=5;
						  else if(stk_op[top_op]=='s') top=6;
						}
							
            stk_op[++top_op]=str[i];
        }
    }

    while(top_op!=-1) work();
    double ans = stk_int[top_int];
		top_int=-1;
		top_op=-1;
		memset(stk_int,0,sizeof(stk_int));
		memset(stk_op,0,sizeof(stk_op));
    return ans;


}

double calc_d(const char str[],const double x_val){
	char temp[100];
	memset(temp,0,sizeof(temp));
	strcpy(temp,str);
	strcat(temp,"\r\n");
		printf(temp);
    //scanf("%s",str);
    //gets(str);
    //printf("%c",str[1]);

/*
    int sum=0;

    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]=='(') sum++;
        if(str[i]==')') sum--;
        if(sum<0){
            legal=false;
            break;
        }
   }
	*/
        
    
		/*
		for(int i=0;i<strlen(str);i++){
    	if(str[i]=='-'&&!isdigit(str[i-1])){
        	strinst(str,i,'0');
        	i++;
        	//printf("%s\n",str);
		}
	}
		*/
/*
    for(int i=1;i<strlen(str);i++){
        if(
            //( is_op(str[i]) && is_op(str[i-1]) ) || 
            ( is_op(str[i]) && str[i-1] == '(' ) ||
            ( is_op(str[i-1]) && str[i] == ')' ) ||
            ( str[i] == '(' && isdigit(str[i-1]) ) ||
            ( isdigit(str[i]) && str[i-1] == ')')
        ){
            legal=false;
            break;
        }
    }
	*/
    /*
    if(sum||!legal||(strlen(str) == 2 && is_op(str[0])))
    {
        printf("no");
        //to judge it's right
    }
		*/

    for(int i=0;i<strlen(str);i++)
    {
        if(isdigit(str[i])){
            double x=0;
            while(i<strlen(str) && isdigit(str[i])){
                x=x*10+str[i++]-'0';
            }
            i--;
            stk_int[++top_int]=x;
        }
        else if(str[i]=='(') stk_op[++top_op]=str[i];
        else if(str[i]==')'){
            while(stk_op[top_op]!='(') work();
            //printf("%d\n",stk_op[top_op]!='(');
            top_op--;
        }
				else if(str[i]=='.'){
        	i++;
        	int n=-1;
        	
        	while(i<strlen(str) && isdigit(str[i])){
        		stk_int[top_int]+=pow(10,n)*(str[i++]-'0');
        		n--;
					}
					i--;
				}else if(str[i]=='s'){
						i+=2;
						stk_op[++top_op]='s';
				}else if(str[i]=='c'){
						i+=2;
						stk_op[++top_op]='c';
				}else if(str[i]=='t'){
						i+=2;
					  stk_int[++top_op]='t';
				}else if(str[i]=='l'){
						if(str[i+1]=='n'){
								i++;
								stk_op[++top_op]='l';
						}else{
							i+=2;
								stk_op[++top_op]='g';
						}
				}else if(str[i]=='e'){
							stk_int[++top_int]=2.7182818285;
				}else if(str[i]=='p'){
						i++;
							stk_int[++top_int]=3.14159265358979;
				}else if(str[i]=='a'){
						if(str[i+3]=='s'){
								i+=5;
								stk_op[++top_op]='i';
						}else if(str[i+3]=='c'){
								i+=5;
								stk_op[++top_op]='o';
						}else if(str[i+3]=='t'){
								i+=5;
								stk_op[++top_op]='p';
						}
				}else if(str[i]=='!'){
						stk_op[++top_op]='!';
				}else if(str[i]=='x'){
						stk_int[++top_int]=x_val;
				}
        else{
            int top=0,cur=0;
            if(stk_op[top_op]=='+') top=1;
            else if(stk_op[top_op]=='-') top=2;
            else if(stk_op[top_op]=='*') top=3;
            else if(stk_op[top_op]=='/') top=4;
						else if(stk_op[top_op]=='^') top=5;
						else if(stk_op[top_op]=='s') top=6;

            if(str[i]=='+') cur=1;
            else if(str[i]=='-') cur=2;
            else if(str[i]=='*') cur=3;
            else if(str[i]=='/') cur=4;
						else if(str[i]=='^') cur=5;
						else if(str[i]=='s') cur=6;

					while(top_op>-1 && pr[top]>=pr[cur] && str[i]!='^' && stk_op[top_op]!='('){
								work();
							
							if(stk_op[top_op]=='+') top=1;
							else if(stk_op[top_op]=='-') top=2;
							else if(stk_op[top_op]=='*') top=3;
							else if(stk_op[top_op]=='/') top=4;
							else if(stk_op[top_op]=='^') top=5;
						  else if(stk_op[top_op]=='s') top=6;
						}
							
            stk_op[++top_op]=str[i];
        }
    }

    while(top_op!=-1) work();
    
    //printf("%d",stk_int[top_int]);
    double ans = stk_int[top_int];
		top_int=-1;
		top_op=-1;
		memset(stk_int,0,sizeof(stk_int));
		memset(stk_op,0,sizeof(stk_op));
    return ans;
		
}


const double N=0.00001;


double value_2(double a,double b,double c,double x){
	return a*x*x+b*x+c;
}

double value_3(double a,double b,double c,double d,double x){
	return a*x*x*x+b*x*x+c*x+d;
}

double value_4(double a,double b,double c,double d, double e,double x){
	return a*x*x*x*x+b*x*x*x+c*x*x+d*x+e;
}


double solve_2(double a,double b,double c){
		double x0=1000,x1;
	do{
		x1=x0;
		double k=2*a*x0+b;
		x0=-value_2(a,b,c,x0)/k+x0;
	}while(fabs(x0-x1)>N);
	return x0;
}

double solve_3(double a,double b,double c,double d){
		double x0=1000,x1;
	do{
		x1=x0;
		double k=3*a*x0*x0+b*2*x0+c;
		x0=-value_3(a,b,c,d,x0)/k+x0;
	}while(fabs(x0-x1)>N);
	return x0;
}

double solve_4(double a,double b,double c,double d,double e){
		double x0=1000,x1;
	do{
		x1=x0;
		double k=4*a*x0*x0*x0+3*b*x0*x0+c*x0+d;
		x0=-value_4(a,b,c,d,e,x0)/k+x0;
		
	}while(fabs(x0-x1)>N);
	return x0;
}

double value(const char str[],double a){
		char s[100];
	//strcpy(s,str);
	//char temp[100];
	strcpy(s,str);
	//int b=(int)a;
		//sprintf(temp,"%d",b);
	//int len = strlen(temp);
	/*
		for(int i=0;i<strlen(s);i++){
				if(s[i]=='x'){
						for(int u=1;u<len;u++){
								strcat(s,"1");
						}
						for(int j=strlen(s)-1;j>i;j--){
								s[j+len-1]=s[j];
						}
						for(int k=i,p=0;p<len;k++,p++){
								s[k]=temp[p];
						}
					
					//s[i]=(char)a;
				}
		}
		*/
		double ans=calc_d(str,a);
		return ans;
}

double solve(const char str[]){
	double x0=10.00,x1;
	double v1,v2;
	do{
			x1=x0;
		double n=x1-0.0001;
		v1=calc_d(str,x1),v2=calc_d(str,n);
			double k=(v1-v2)/0.0001;
			x0=-v1/k+x1;
			char s[100];
			char c[100];
		char x[100];
		char t[100];
			sprintf(s,"%lf",x0);
			strcat(s,"  ");
			sprintf(c,"%lf",k);
			strcat(s,c);
			sprintf(x,"%lf",value(str,x1));
		sprintf(t,"%lf",v2);
		strcat(s," ");
		strcat(s,x);
		strcat(s," ");
		strcat(s,t);
		 strcat(s,"\r\n");
			printf(s);
	}while(fabs(x0-x1)>2e-6);
	return x0;
}

const double gap=0.00001;
double calc_def(const char str[],double st,double end){
		double ans=(calc_d(str,st)+calc_d(str,end))/2;
	  int n=1000,i;
		
		double h=(end-st)/n;
		for(i=1;i<n;i++){
				ans+=calc_d(str,st+i*h);
				char temp[100];
				sprintf(temp,"%.4lf",ans);
				printf(temp);
		}
		return ans*h;
}