#include <Origin.h>
///////////////////////////////////////////////////////////////////////////
void doCal()
{	
	Worksheet wks1 = wksPage.Layers("YFP Ch1"); // yfp channel data
	Worksheet wks2 = wksPage.Layers("CFP Ch2"); // cfp channel data

// wks 3: matched pairs of overlapping bacteria and their Fl intensities
	Worksheet wks3 = wksPage.Layers("pari");	if(!wks1||!wks2||!wks3 )
		return;
	
	Column colA1 = wks1.Columns("A");  // get column A in worksheet
	Column colB1 = wks1.Columns("B");  // get column B in worksheet
	Column colC1 = wks1.Columns("C");  // get column C in worksheet
	Column colD1 = wks1.Columns("D");  // get column D in worksheet
	Column colE1 = wks1.Columns("E");  // get column E in worksheet
	Column colF1 = wks1.Columns("F");  // get column F in worksheet
	
	Column colA2 = wks2.Columns("A");  
	Column colB2 = wks2.Columns("B");  
	Column colC2 = wks2.Columns("C");  
	Column colD2 = wks2.Columns("D");  
	Column colE2 = wks2.Columns("E");  
	Column colF2 = wks2.Columns("F");  
	
	Column colA3 = wks3.Columns("A");  
	Column colB3 = wks3.Columns("B");  
	Column colC3 = wks3.Columns("C");  
	Column colD3 = wks3.Columns("D");  
	Column colE3 = wks3.Columns("E");  
	Column colF3 = wks3.Columns("F");  
	Column colG3 = wks3.Columns("G");  	
	if(!colA1 || !colB1 || !colC1)
		return;
//get output data of ImageJ image analysis, where each bacterium has //its Center of mass – image coordinates xm, xy, id, area and mean
// yfp channel
	vectorbase& vA1 = colA1.GetDataObject();//get data of col A (id)
	vectorbase& vB1 = colB1.GetDataObject();//get data of col B (area)
	vectorbase& vC1 = colC1.GetDataObject();//get data of col C (mean)
	vectorbase& vD1 = colD1.GetDataObject();//get data of col D(xm)
	vectorbase& vE1 = colE1.GetDataObject();//get data of col E(ym)
	// cfp channel
	vectorbase& vA2 = colA2.GetDataObject();
vectorbase& vB2 = colB2.GetDataObject();    
	vectorbase& vC2 = colC2.GetDataObject();	
	vectorbase& vD2 = colD2.GetDataObject();  
	vectorbase& vE2 = colE2.GetDataObject();
	// make the third sheet ready
	vectorbase& vA3 = colA3.GetDataObject();  // address the column
	vectorbase& vB3 = colB3.GetDataObject();  // address the column
	vectorbase& vC3 = colC3.GetDataObject();
	vectorbase& vD3 = colD3.GetDataObject();
	vectorbase& vE3 = colE3.GetDataObject();
	vectorbase& vF3 = colF3.GetDataObject();
	vectorbase& vG3 = colG3.GetDataObject(); 
	double min=10000; // such large distance cannot exist on image
	int iRow1_min;	// the row of yfp cell
	int iRow2_min;	// the row of matched cfp cell
	double dist;	
	int colD1_meja=colD1.GetNumRows(); // how many lines
	int colD2_meja=colD2.GetNumRows();

//scan the data and compare the distance among two bacteria on the two //channels
	for(int iRow1=0; iRow1<colD1_meja; iRow1++)	{		
		for(int iRow2=0; iRow2<colD2_meja; iRow2++)
		{		
			double dist_x = (vD1[iRow1]-vD2[iRow2])^2;
			double dist_y = (vE1[iRow1]-vE2[iRow2])^2;
			double sum=dist_x+dist_y;
			dist = (sqrt(sum));

			// the smallest distance of all possible comparisons
			if (dist<min)			
{
				min=dist;
				iRow1_min=iRow1;
				iRow2_min=iRow2;	
			}			
		}		
//if the pair is correctly matched the distance has to be less then 5 pix
// and already matched cells can not be matched once again
if ((min<5)&&(vA2[iRow2_min]!=0))
		{		
			vA3[iRow1]=vA1[iRow1_min];// id of yfp cells
			vB3[iRow1]=vA2[iRow2_min]; // id of cfp cell
			vE3[iRow1]=min;		  //dist.between yfp cfp cell	
			vC3[iRow1]=vC1[iRow1_min];// mean Fl int of yfp cell
			vD3[iRow1]=vC2[iRow2_min]; // mean Fl int of cfp cell
			vF3[iRow1]=vB1[iRow1_min];// mean area of yfp cell
			vG3[iRow1]=vB2[iRow2_min]; // mean area of cfp cell
			vA2[iRow2_min]=0;		// the cell was matched
		}
			
	}
}
int test()    //main      
{                                                           
doCal();
   	return 0; // Exit our function, returning zero to the caller
}
