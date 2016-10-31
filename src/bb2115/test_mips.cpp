#include "mips.h"
#include "test_mips_tests.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;


int main(){

    mips_mem_h mem = mips_mem_create_ram(4096);

    mips_cpu_h cpu=mips_cpu_create(mem);

    mips_error e=mips_cpu_set_debug_level(cpu, 4, stderr);
    if(e!=mips_Success){
        fprintf(stderr, "mips_cpu_set_debug_level : failed.\n");
        exit(1);
    }


    mips_test_begin_suite();

    	cout << endl;

        testadd(mem, cpu,
        		13, 900,
    		    27, 234,
    			4);
        testadd(mem, cpu,
        		13, 900,
    		    27, 234,
    			0);
        testadd(mem, cpu,
        		10, 900,
    		    11, -234,
    			5);
        testadd(mem, cpu,
        		10, -900,
    		    11, -234,
    			5);
        testadd(mem, cpu,
        		10, -900,
    		    11, 234,
    			5);

        cout << endl;

        testaddu(mem, cpu,
        		13, 900,
    		    27, 234,
    			4);
        testaddu(mem, cpu,
        		13, 900,
    		    27, 234,
    			0);
        testaddu(mem, cpu,
        		10, 900,
    		    11, -234,
    			5);
        testaddu(mem, cpu,
        		10, -900,
    		    11, -234,
    			5);
        testaddu(mem, cpu,
        		10, -900,
    		    11, 234,
    			5);

        cout << endl;

        testaddi(mem, cpu,
        		13, 900,
    		    234,
    			4);
        testaddi(mem, cpu,
        		13, 900,
    		    234,
    			0);
        testaddi(mem, cpu,
        		10, 900,
    		    -234,
    			5);
        testaddi(mem, cpu,
        		10, -900,
    		    -234,
    			5);
        testaddi(mem, cpu,
        		10, -900,
    		    234,
    			5);

        cout << endl;

        testaddiu(mem, cpu,
        		13, 900,
    		    234,
    			4);
        testaddiu(mem, cpu,
        		13, 900,
    		    234,
    			0);
        testaddiu(mem, cpu,
        		10, 900,
    		    -234,
    			5);
        testaddiu(mem, cpu,
        		10, -900,
    		    -234,
    			5);
        testaddiu(mem, cpu,
        		10, -900,
    		    234,
    			5);

        cout << endl;

        testand(mem, cpu,
        		13, 900,
    		    27, 234,
    			4);
        testand(mem, cpu,
        		13, 900,
    		    27, 234,
    			0);
        testand(mem, cpu,
        		10, 900,
    		    11, -234,
    			5);
        testand(mem, cpu,
        		10, -900,
    		    11, -234,
    			5);
        testand(mem, cpu,
        		10, -900,
    		    11, 234,
    			5);

        cout << endl;

        testandi(mem, cpu,
        		13, 900,
    		    234,
    			4);
        testandi(mem, cpu,
        		13, 900,
    		    234,
    			0);
        testandi(mem, cpu,
        		10, 900,
    		    -234,
    			5);
        testandi(mem, cpu,
        		10, -900,
    		    -234,
    			5);
        testandi(mem, cpu,
        		10, -900,
    		    234,
    			5);

    	cout << endl;

        testbeq(mem, cpu,
        		13, 900,
    		    27, 900,
    			5);
        testbeq(mem, cpu,
        		13, 900,
    		    27, 900,
    			0);
        testbeq(mem, cpu,
        		10, 900,
    		    11, -234,
    			2);
        testbeq(mem, cpu,
        		10, -900,
    		    11, -900,
    			80);
        testbeq(mem, cpu,
        		10, -900,
    		    11, 900,
    			5);

    	cout << endl;

        testbgez(mem, cpu,
        		13, 900,
    			4);;
        testbgez(mem, cpu,
        		13, 0,
    			5);
        testbgez(mem, cpu,
        		10, 900,
    			0);
        testbgez(mem, cpu,
        		10, -2,
    			12);
        testbgez(mem, cpu,
        		10, 2,
    			1);					// TRY NEGATIVE

    	cout << endl;

        testbgezal(mem, cpu,
        		13, 900,
    			4);;
        testbgezal(mem, cpu,
        		13, 0,
    			5);
        testbgezal(mem, cpu,
        		10, 900,
    			0);
        testbgezal(mem, cpu,
        		10, -2,
    			12);
        testbgezal(mem, cpu,
        		10, 2,
    			1);

        cout << endl;

        testbgtz(mem, cpu,
        		13, 900,
    			4);
        testbgtz(mem, cpu,
        		13, 0,
    			5);
        testbgtz(mem, cpu,
        		10, 900,
    			0);
        testbgtz(mem, cpu,
        		10, -2,
    			12);
        testbgtz(mem, cpu,
        		10, 2,
    			1);					// TRY NEGATIVE

        cout << endl;

        testblez(mem, cpu,
        		13, 900,
    			400);
        testblez(mem, cpu,
        		13, 0,
    			100);
        testblez(mem, cpu,
        		10, 0,
    			5);
        testblez(mem, cpu,
        		10, -900,
    			0);
        testblez(mem, cpu,
        		10, -900,
    			60);

        cout << endl;

        testbltz(mem, cpu,
        		13, 900,
    			400);
        testbltz(mem, cpu,
        		13, 0,
    			100);
        testbltz(mem, cpu,
        		10, 0,
    			5);
        testbltz(mem, cpu,
        		10, -900,
    			0);
        testbltz(mem, cpu,
        		10, -900,
    			60);

        cout << endl;

        testbltzal(mem, cpu,
        		13, 900,
    			400);
        testbltzal(mem, cpu,
        		13, 0,
    			100);
        testbltzal(mem, cpu,
        		10, 0,
    			5);
        testbltzal(mem, cpu,
        		10, -900,
    			0);
        testbltzal(mem, cpu,
        		10, -900,
    			60);

        cout << endl;

        testbne(mem, cpu,
        		13, 900,
    		    27, 900,
    			400);
        testbne(mem, cpu,
        		13, 900,
    		    27, 900,
    			100);
        testbne(mem, cpu,
        		10, 900,
    		    11, -234,
    			5);
        testbne(mem, cpu,
        		10, -900,
    		    11, -900,
    			0);
        testbne(mem, cpu,
        		10, -900,
    		    11, 900,
    			60);

        cout << endl;
        									//PROBLEMS WITH NEGATIVE
	    testj(mem, cpu,
			   15);
	    testj(mem, cpu,
			   3);
	    testj(mem, cpu,
			   100);
	    testj(mem, cpu,
			   2);
	    testj(mem, cpu,
			   0);

        cout << endl;
        									//PROBLEMS WITH NEGATIVE
	    testjal(mem, cpu,
			   15);
	    testjal(mem, cpu,
			   3);
	    testjal(mem, cpu,
			   100);
	    testjal(mem, cpu,
			   2);
	    testjal(mem, cpu,
			   0);

        cout << endl;
        									//PROBLEMS WITH NEGATIVE
	    testjalr(mem, cpu,
	    		15, 12,
				31);
	    testjalr(mem, cpu,
	    		12, 16,
				3);
	    testjalr(mem, cpu,
	    		14,  0,
				10);
	    testjalr(mem, cpu,
	    		13, 36,
				2);
	    testjalr(mem, cpu,
	    		1, 100,
				6);

        cout << endl;
        									//PROBLEMS WITH NEGATIVE
	    testjr(mem, cpu,
			   15, 0);
	    testjr(mem, cpu,
			   3, 4);
	    testjr(mem, cpu,
			   31, 100);
	    testjr(mem, cpu,
			   2, 16);
	    testjr(mem, cpu,
			   28, 12);

    	cout << endl;

		testlb(mem, cpu,
				13, 900,
				28,
				4);
		testlb(mem, cpu,
				13, 4,
				16,
				0);
		testlb(mem, cpu,
				10, 900,
				12,
				5);
		testlb(mem, cpu,
				10, 60,
				0,
				5);
		testlb(mem, cpu,
				10, 0,
				24,
				5);

    	cout << endl;

		testlbu(mem, cpu,
				13, 900,
				28,
				4);
		testlbu(mem, cpu,
				13, 4,
				16,
				0);
		testlbu(mem, cpu,
				10, 900,
				12,
				5);
		testlbu(mem, cpu,
				10, 60,
				0,
				5);
		testlbu(mem, cpu,
				10, 0,
				24,
				5);

    	cout << endl;

		testlh(mem, cpu,
				13, 900,
				28,
				4);
		testlh(mem, cpu,
				13, 4,
				16,
				0);
		testlh(mem, cpu,
				10, 900,
				12,
				5);
		testlh(mem, cpu,
				10, 60,
				0,
				5);
		testlh(mem, cpu,
				10, 0,
				24,
				5);

    	cout << endl;

		testlhu(mem, cpu,
				13, 900,
				28,
				4);
		testlhu(mem, cpu,
				13, 4,
				16,
				0);
		testlhu(mem, cpu,
				10, 900,
				12,
				5);
		testlhu(mem, cpu,
				10, 60,
				0,
				5);
		testlhu(mem, cpu,
				10, 0,
				24,
				5);

        cout << endl;

	    testlui(mem, cpu,
			   300,
			   7);
	    testlui(mem, cpu,
			   300,
			   0);
	    testlui(mem, cpu,
			   -300,
			   16);
	    testlui(mem, cpu,
			   5,
			   9);
	    testlui(mem, cpu,
			   -300,
			   29);

    	cout << endl;

		testlw(mem, cpu,
				13, 900,
				28,
				4);
		testlw(mem, cpu,
				13, 4,
				16,
				0);
		testlw(mem, cpu,
				10, 900,
				12,
				5);
		testlw(mem, cpu,
				10, 60,
				0,
				5);
		testlw(mem, cpu,
				10, 0,
				24,
				5);

	    cout << endl;

        testor(mem, cpu,
        		13, 900,
    		    27, 234,
    			4);
        testor(mem, cpu,
        		13, 900,
    		    27, 234,
    			0);
        testor(mem, cpu,
        		10, 900,
    		    11, -234,
    			5);
        testor(mem, cpu,
        		10, -900,
    		    11, -234,
    			5);
        testor(mem, cpu,
        		10, -900,
    		    11, 234,
    			5);

        cout << endl;

        testori(mem, cpu,
        		13, 900,
    		    234,
    			4);
        testori(mem, cpu,
        		13, 900,
    		    234,
    			0);
        testori(mem, cpu,
        		10, 900,
    		    -234,
    			5);
        testori(mem, cpu,
        		10, -900,
    		    -234,
    			5);
        testori(mem, cpu,
        		10, -900,
    		    234,
    			5);

	    cout << endl;

		testsb(mem, cpu,
				13, 900,
				28, 14,
				4);
		testsb(mem, cpu,
				13, 4,
				16, -30,
				0);
		testsb(mem, cpu,
				10, 900,
				12, 0,
				8);
		testsb(mem, cpu,
				10, 60,
				27, 200,
				4);
		testsb(mem, cpu,
				10, 0,
				24, 444,
				4);

	    cout << endl;

		testsh(mem, cpu,
				13, 900,
				28, 14,
				4);
		testsh(mem, cpu,
				13, 4,
				16, -30,
				0);
		testsh(mem, cpu,
				10, 900,
				12, 0,
				8);
		testsh(mem, cpu,
				10, 60,
				27, 200,
				4);
		testsh(mem, cpu,
				10, 0,
				24, 444,
				4);

        cout << endl;

        testsll(mem, cpu,
        		5, 100,
        		4,
        		5);
        testsll(mem, cpu,
        		5, -100,
        		20,
        		10);
        testsll(mem, cpu,
        		5, 100,
        		6,
        		3);
        testsll(mem, cpu,
        		13, -100,
        		-1,
        		27);
        testsll(mem, cpu,
        		5, 100,
        		4,
        		0);

        cout << endl;

        testsllv(mem, cpu,
        		25, 300,
        		10, 5,
        		9);
        testsllv(mem, cpu,
        		25, 300,
        		10, 5,
        		0);
        testsllv(mem, cpu,
        		25, -300,
        		10, 5,
        		9);
        testsllv(mem, cpu,
        		25, 300,
        		10, -5,
        		9);
        testsllv(mem, cpu,
        		25, -300,
        		10, -5,
        		9);

        cout << endl;

        testslt(mem, cpu,
        		13, 607,
        		29, 23,
        		3);
        testslt(mem, cpu,
        		13, 607,
        		29, 23,
        		0);
        testslt(mem, cpu,
        		13, -607,
        		29, 23,
        		3);
        testslt(mem, cpu,
        		13, 607,
        		29, -23,
        		3);
        testslt(mem, cpu,
        		13, -607,
        		29, -23,
        		3);

        cout << endl;

        testslti(mem, cpu,
        		13, 607,
        		23,
        		3);
        testslti(mem, cpu,
        		13, 607,
        		23,
        		0);
        testslti(mem, cpu,
        		13, -607,
        		23,
        		3);
        testslti(mem, cpu,
        		13, 607,
        		-23,
        		3);
        testslti(mem, cpu,
        		13, -607,
        		-23,
        		3);

        cout << endl;

        testsltiu(mem, cpu,
        		13, 607,
        		23,
        		3);
        testsltiu(mem, cpu,
        		13, 607,
        		23,
        		0);
        testsltiu(mem, cpu,
        		13, -607,
        		23,
        		3);
        testsltiu(mem, cpu,
        		13, 607,
        		-23,
        		3);
        testsltiu(mem, cpu,
        		13, -607,
        		-23,
        		3);

        cout << endl;

        testsltu(mem, cpu,
        		13, 607,
        		29, 23,
        		3);
        testsltu(mem, cpu,
        		13, 607,
        		29, 23,
        		0);
        testsltu(mem, cpu,
        		13, -607,
        		29, 23,
        		3);
        testsltu(mem, cpu,
        		13, 607,
        		29, -23,
        		3);
        testsltu(mem, cpu,
        		13, -607,
        		29, -23,
        		3);

        cout << endl;

        testsra(mem, cpu,
        		5, 100,
        		4,
        		5);
        testsra(mem, cpu,
        		5, -100,
        		20,
        		10);
        testsra(mem, cpu,
        		5, 100,
        		6,
        		3);
        testsra(mem, cpu,
        		13, -100,
        		-1,
        		27);
        testsra(mem, cpu,
        		5, 100,
        		4,
        		0);

        cout << endl;

        testsrav(mem, cpu,
        		25, 300,
        		10, 5,
        		9);
        testsrav(mem, cpu,
        		25, 300,
        		10, 5,
        		0);
        testsrav(mem, cpu,
        		25, -300,
        		10, 5,
        		9);
        testsrav(mem, cpu,
        		25, 300,
        		10, -5,
        		9);
        testsrav(mem, cpu,
        		25, -300,
        		10, -5,
        		9);

        cout << endl;

        testsrl(mem, cpu,
        		5, 100,
        		4,
        		5);
        testsrl(mem, cpu,
        		5, -100,
        		20,
        		10);
        testsrl(mem, cpu,
        		5, 100,
        		6,
        		3);
        testsrl(mem, cpu,
        		13, -100,
        		-1,
        		27);
        testsrl(mem, cpu,
        		5, 100,
        		4,
        		0);

        cout << endl;

        testsrlv(mem, cpu,
        		25, 300,
        		10, 5,
        		9);
        testsrlv(mem, cpu,
        		25, 300,
        		10, 5,
        		0);
        testsrlv(mem, cpu,
        		25, -300,
        		10, 5,
        		9);
        testsrlv(mem, cpu,
        		25, 300,
        		10, -5,
        		9);
        testsrlv(mem, cpu,
        		25, -300,
        		10, -5,
        		9);

        cout << endl;

        testsub(mem, cpu,
        		13, 900,
    		    27, 234,
    			4);
        testsub(mem, cpu,
        		13, 900,
    		    27, 234,
    			0);
        testsub(mem, cpu,
        		10, 900,
    		    11, -234,
    			5);
        testsub(mem, cpu,
        		10, -900,
    		    11, -234,
    			5);
        testsub(mem, cpu,
        		10, -900,
    		    11, 234,
    			5);

        cout << endl;

        testsubu(mem, cpu,
        		13, 900,
    		    27, 234,
    			4);
        testsubu(mem, cpu,
        		13, 900,
    		    27, 234,
    			0);
        testsubu(mem, cpu,
        		10, 900,
    		    11, -234,
    			5);
        testsubu(mem, cpu,
        		10, -900,
    		    11, -234,
    			5);
        testsubu(mem, cpu,
        		10, -900,
    		    11, 234,
    			5);

        cout << endl;


		testsw(mem, cpu,
				13, 900,
				28, 14,
				4);
		testsw(mem, cpu,
				13, 4,
				16, -30,
				0);
		testsw(mem, cpu,
				10, 900,
				12, 0,
				8);
		testsw(mem, cpu,
				10, 60,
				27, 200,
				4);
		testsw(mem, cpu,
				10, 0,
				24, 444,
				4);

	    cout << endl;


        testxor(mem, cpu,
        		13, 900,
    		    27, 234,
    			4);
        testxor(mem, cpu,
        		13, 900,
    		    27, 234,
    			0);
        testxor(mem, cpu,
        		10, 900,
    		    11, -234,
    			5);
        testxor(mem, cpu,
        		10, -900,
    		    11, -234,
    			5);
        testxor(mem, cpu,
        		10, -900,
    		    11, 234,
    			5);

        cout << endl;


//      random testing seemed like a good idea at the time...
//
//      srand(time(NULL));
//
//      for(int i = 0; i < 10; i++){
//    	  testadd(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testaddi(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testaddiu(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testaddu(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testand(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testandi(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testbeq(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 500 + (-500)));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testbne(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 500 + (-500)));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testlui(mem, cpu,
//    			  (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testor(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testori(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsll(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsllv(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testslt(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testslti(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsltiu(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsltu(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsra(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsrav(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsrl(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsrlv(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsub(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testsubu(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }
//
//      for(int i = 0; i < 10; i++){
//    	  testxor(mem, cpu,
//    			  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0), (rand() % 500 + (-500)),
//				  (rand() % 31 + 0));
//      }

    mips_test_end_suite();

    return 0;
}

