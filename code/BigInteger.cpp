#include "BigInteger.h"

#include "iostream"
#include <string.h>
#include <stdlib.h>
using namespace std;

BigInteger::BigInteger(const char* str) {
	//------------------------------------
	// alpha=10^19 < beta=2^64
	// read the string by 19 characters.
	//------------------------------------
	int str_size = strlen(str); 
	int str_size_div_19 = str_size/19;
	int str_size_rem_19 = str_size%19;

	n = (str_size_rem_19 == 0) ? str_size_div_19
		                 : str_size_div_19+1;
	uint64_t  b_data[n];
	uint64_t* b = b_data;
	//------------------------------------
	// read the string from the left
	//------------------------------------
	b += n-1;
	if( str_size_rem_19 > 0 ) {
		uint64_t digit = 0;
		for(int j = 0; j < str_size_rem_19; j++, str++) {
            digit = 10 * digit + uint64_t(*str-'0');
        }
		*b=digit; b--;
	}

	for(int i=0;i<str_size_div_19;i++,b--) {
		uint64_t digit = 0;
		for(int j = 0; j < 19; j++, str++) {
            digit = 10 * digit + uint64_t(*str-'0');
        }
		*b = digit;
	}
	b++;
	//----------------------------------------------------
	// change from base alpha to base beta
	// bigint = b[n-1]*alpha^(n-1)+...+b[0]*alpha^0
	//        = a[n-1]*beta ^(n-1)+...+a[0]*beta ^0
	// see 3.3 basic integer arithmetic
	// page 59, A computational introduction.. N.T.A.
	// by Victor Shoup, 2nd edition
	//----------------------------------------------------
	uint64_t alpha = 10000000000000000000ull;
	n_max = n+5;
	
	// posix_memalign((void **)&data, 64, n_max * sizeof(uint64_t));
	data = (uint64_t*)aligned_alloc(64,n_max*sizeof(uint64_t));

	for(int j = 0; j < n; j++) {
		uint64_t hi = 0;
		for(int i = n-1; i >= 0; i--) {
			//-------------------------------
			// tmp <=(beta-1)*beta+beta-1<beta^2
			// no overflow
			//-------------------------------
			__uint128_t tmp = (__uint128_t(hi)) * alpha + b[i];
			hi   = (uint64_t)(tmp)   ; // hi   = tmp % beta
			b[i] =            tmp>>64; // b[i] =[tmp / beta]
		}
		data[j]=hi;
	}
	//----------------------------------------------------
	// reduce the size when Most Siginificant Digit
	// is zero.
	//----------------------------------------------------
	for(int i = n-1; i >= 0; i--) {
        if (data[i] == 0) {
            n--;
        } 
        else {
		    break;
        }
    }
		
		
}

void BigInteger::print_dec() const {
	// printf("-------------------- %s ---------------------\n",name);
	// cout << name << " = ";

	//----------------------------------------------------
	// change from base beta=2^64 to base alpha=10^19
	// bigint = a[n-1]*beta ^(n-1)+...+a[0]*beta ^0
	//        = b[m-1]*alpha^(m-1)+...+b[0]*alpha^0
	// see 3.3 basic integer arithmetic
	// page 59, A computational introduction.. N.T.A.
	// by Victor Shoup, 2nd edition
	//
	// bigint < beta^n < alpha^(2n), so take m=2n, initially.
	//----------------------------------------------------
	uint64_t alpha = 10000000000000000000ull;
	int m = 2 * n;
	uint64_t a[n]; for(int i=0;i<n;i++) a[i]=data[i];
	uint64_t b[m];
	for(int j=0;j<m;j++)
	{
		uint64_t hi=0;
		for(int i=n-1;i>=0;i--)
		{
			//-------------------------------------
			// tmp <=(alpha-1)*beta+beta-1
			//     <  alpha*beta < beta^2
			// hi < alpha < beta
			// a[i]       < beta 
			// So, no overflow for each three case.
			//--------------------------------------
			__uint128_t tmp = (__uint128_t(hi)<<64) + a[i];
			hi   = (uint64_t)(tmp % alpha);
			a[i] = (uint64_t)(tmp / alpha);
		}
		b[j]=hi;
	}
	//----------------------------------------------------
	// reduce the size when Most Siginificant Digit
	// is zero.
	//----------------------------------------------------
	for(int i=m-1;i>=0;i--)
		if(b[i]==0)  m--  ;
		else	     break;
	//----------------------------------------------------
	// print out
	//----------------------------------------------------
	// printf("%" PRIu64 "*(10^%d)+",b[m-1],(m-1)*19);
	cout << b[m-1] << "*(10^" << (m-1) * 19 << ")+";
	for(int i = m - 2; i >= 1; i--) {
		cout << b[i] << "*(10^" << i * 19 << ")+";
		// printf("%" PRIu64 "*(10^%d)+",b[i],i*19);
	}
	cout << b[0] << endl;
	// printf("%" PRIu64 " \n",b[0]);
}

void parallelAddition(const BigInteger*& A, BigInteger& B, long N) {

}