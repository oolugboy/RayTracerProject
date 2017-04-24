////////////////////////////////////////
// Bitmap.h
////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////

class Bitmap {
public:
	Bitmap(int x,int y)						
	{
		xRes=x; 
		yRes=y; 
		pixel=new int[xRes*yRes];
	}
	~Bitmap()								
	{
		delete [] pixel;
	}

	bool SaveBMP(const char *filename);

	int GetxRes() const						
	{
		return xRes;
	}
	int GetyRes() const						
	{
		return yRes;
	}
	int &GetPixel(int x,int y)				
	{
		return pixel[y*xRes+x];
	}
	void SetPixel(int x,int y,int pix)		
	{
		pixel[y*xRes+x]=pix;
	}

private:
	int xRes;
	int yRes;
	int *pixel;
};

////////////////////////////////////////////////////////////////////////////////
