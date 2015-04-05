/* Mangea Liviu Darius 334CA */

#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>
#include <time.h>


#define PI 3.14159265358979323846
#define inf 1000000
#define WATER Color(0.1f, 0.4f, 0.8f)
#define GRASS Color(0.1f, 0.5f, 0.2f)
#define TERRAIN Color(0.8f, 0.5f, 0.25f)
#define SELECTED Color(1, 0.5f, 0.5f)
#define BLACK Color(0,0,0)

using namespace std;


vector <Object3D*> objects;
Visual2D *v2d1;
Object3D *cube11,*cube21,*cube31, *cube41, *cube[30][30], *cube2[30][30];
Object3D *piata[10];
Object3D *casa[100];
Object3D *drum[100];
Object3D *mark[100];
Object3D *relief[100];
vector <Face*> faces;
vector <Point3D*> vertices2[10];
vector <Point3D*> vertices3[100];
vector <Point3D*> vertices4[100];
vector <Point3D*> vertices5[100];
vector <Point3D*> vertices6[100];
Object3D *house[100];
Color color_prev;


float n=1;
float incX = -700.0f, incY = 300.0f;
int i, j, k;
int mod = 0;
int move_land_x = 15, move_land_y = 15;
int construibil[30][30];
int contor_piata = 0;
int contor_casa = 0;
int contor_drum = 0;
int contor_mark = 0;
int contor_house = 0;
int contor_relief = 0;
int nr_casa = 0;
int suprapunere = 0;
int orientare = 0;
int xx1, xx2, xx3, yy1, yy2, yy3;
float casaX[100], casaY[100];
float X1[100], Y1[100], X2[100], Y2[100], X3[100], Y3[100];
int ok = 0, r, rr;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0.0f,0.0f,(float)DrawingWindow::width,(float)DrawingWindow::height,0,0,DrawingWindow::width,DrawingWindow::height); 
	v2d1->tipTran(true);
	addVisual2D(v2d1);
	
	//se deseneaza un cub
	
	//cele 6 fete
	vector <int> contour;
	//fata jos
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));
	//fata sus
	contour.clear();
	contour.push_back(4);
	contour.push_back(5);
	contour.push_back(6);
	contour.push_back(7);
	faces.push_back(new Face(contour));
	//fata fata
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(5);
	contour.push_back(4);
	faces.push_back(new Face(contour));
	//fata dreapta
	contour.clear();
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(6);
	contour.push_back(5);
	faces.push_back(new Face(contour));
	//fata spate
	contour.clear();
	contour.push_back(2);
	contour.push_back(3);
	contour.push_back(7);
	contour.push_back(6);
	faces.push_back(new Face(contour));
	//fata stanga
	contour.clear();
	contour.push_back(3);
	contour.push_back(0);
	contour.push_back(4);
	contour.push_back(7);
	faces.push_back(new Face(contour));


	vector <Point3D*> vertices1[30][30];

	for(i = 0; i < 30; i++) {
		for(j = 0; j < 30; j++) {
			//varfurile de jos
			vertices1[i][j].push_back(new Point3D(50*i,0,50*j));
			vertices1[i][j].push_back(new Point3D(50*i+50,0,50*j));
			vertices1[i][j].push_back(new Point3D(50*i+50,0,50*j+50));
			vertices1[i][j].push_back(new Point3D(50*i,0,50*j+50));
			//varfurile de sus
			vertices1[i][j].push_back(new Point3D(50*i,0,50*j));
			vertices1[i][j].push_back(new Point3D(50*i+50,0,50*j));
			vertices1[i][j].push_back(new Point3D(50*i+50,0,50*j+50));
			vertices1[i][j].push_back(new Point3D(50*i,0,50*j+50));

			cube[i][j] = new Object3D(vertices1[i][j], faces, Color(0,0,0), false);
			addObject3D_to_Visual2D(cube[i][j],v2d1);
			objects.push_back(cube[i][j]);

			cube2[i][j] = new Object3D(vertices1[i][j], faces, TERRAIN, true);
			addObject3D_to_Visual2D(cube2[i][j],v2d1);
			objects.push_back(cube2[i][j]);

			if(i < 4 || i >= 26 || j < 4 || j >= 26) {
				construibil[i][j] = 1;
			}

		}
	}

}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	Transform3D::loadIdentityModelMatrix();
	Transform3D::isometricProjection();
	Transform3D::translateMatrix(incX, incY, 0);
	for(i = 0; i < 30; i++) {
		for(j = 0; j < 30; j++) {
			Transform3D::applyTransform(cube[i][j]);
			Transform3D::applyTransform(cube2[i][j]);
		}
	}
	for(k = 0; k < contor_piata; k++) {
		Transform3D::applyTransform(piata[k]);
	}

	for(k = 0; k < contor_mark; k++) {
		Transform3D::applyTransform(mark[k]);

	}

	for(k = 0; k < contor_drum; k++) {
		Transform3D::applyTransform(drum[k]);

	}

	for(k = 0; k < contor_relief; k++) {
		Transform3D::applyTransform(relief[k]);

	}

	for(k = 0; k < contor_casa; k++) {
		if(k % 3 == 0) {
			if(k >= 3) {
				Transform3D::translateMatrix(-casaX[k/3 - 1] , -casaY[k/3 - 1], 0);
			}
		}
			if(k % 3 == 0) {
				Transform3D::translateMatrix(casaX[k/3] + X1[k/3], casaY[k/3] + Y1[k/3], 0);
			}

			if(k % 3 == 1) {
				Transform3D::translateMatrix(-casaX[k/3] - X1[k/3], -casaY[k/3] - Y1[k/3], 0);
				Transform3D::translateMatrix(casaX[k/3] + X2[k/3], casaY[k/3] + Y2[k/3], 0);
			}

			if(k % 3 == 2) {
				Transform3D::translateMatrix(-casaX[k/3] - X2[k/3], -casaY[k/3] - Y2[k/3], 0);
				Transform3D::translateMatrix(casaX[k/3] + X3[k/3], casaY[k/3] + Y3[k/3], 0);
			}
		Transform3D::applyTransform(casa[k]);
	}

}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(0, 0, width, height); 
	

}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
		/* Tasta de iesit din modurile de editare */
		case 'q' :
			{
				if(mod == 11) {
					if((color_prev.r == SELECTED.r && color_prev.g == SELECTED.g && color_prev.b == SELECTED.b)) {
						color_prev = cube2[move_land_x][move_land_y]->color;
					}
					cube2[move_land_x][move_land_y]->color = Color(1,0,0);
					mod = 10;
					break;
				}

				if(mod == 10) {
					cube2[move_land_x][move_land_y]->color = color_prev;
					mod = 0;
					move_land_x = 15;
					move_land_y = 15;
					color_prev = cube2[15][15]->color;
					break;
				}

				if(mod == 22 || mod == 21) {
					if(construibil[move_land_x][move_land_y] != 1 && construibil[move_land_x][move_land_y] != 3 && suprapunere == 0) {
						for(i = move_land_x - 4; i <= move_land_x + 4; i++) {
							for(j = move_land_y - 4; j <= move_land_y + 4; j++) {
									cube2[i][j]->color.r -= 0.2f;
							}
						}
					}
					cube2[move_land_x][move_land_y]->color = Color(0.3f,0.2f,0.6f);
					mod = 20;
					suprapunere = 0;
					break;
				}

				if(mod == 20) {
					cube2[move_land_x][move_land_y]->color = color_prev;
					mod = 0;
					move_land_x = 15;
					move_land_y = 15;
					color_prev = cube2[15][15]->color;
					break;
				}

				if(mod == 31) {
					mod = 0;
					for(i = 0; i < 30; i++) {
						 for(j = 0; j < 30; j++) {
							 if(construibil[i][j] == 10) {
								 cube2[i][j]->color.r -= 0.2f;
							 }
						 }
					 }
					break;
				}

				if(mod == 30) {
					mod = 0;
					nr_casa++;
					removeObject3D_from_Visual2D(casa[contor_casa -1], v2d1);
					removeObject3D_from_Visual2D(casa[contor_casa - 2], v2d1);
					removeObject3D_from_Visual2D(casa[contor_casa - 3], v2d1);
					for(i = 0; i < 30; i++) {
						 for(j = 0; j < 30; j++) {
							 if(construibil[i][j] == 10) {
								 cube2[i][j]->color.r -= 0.2f;
							 }
						 }
					 }
					break;
				}

				if(mod == 41) {
					mod = 0;
					move_land_x = 15;
					move_land_y = 15;
					break;
				}

				if(mod == 40) {
					cube2[move_land_x][move_land_y]->color = color_prev;
					mod = 0;
					move_land_x = 15;
					move_land_y = 15;
					color_prev = cube2[15][15]->color;
					break;
				}
			}
		break;
		


		/* Taste scroll */
		case 'a' : 
			{ 
				incX += 100; 
			}
		break;

		case 's' : 
			{	
				incY += 100; 
			 
			}
		break;
		
		case 'd' : 
			{
				incX -= 100; 
			}
				
		break;
		
		case 'w' : 
			{ 
				incY -= 100;
			}
		break;


		/* Taste miscare a cursorului/obiectelor */
		case 'l' : 
			{ 
				 if(mod == 10) {
					 if(move_land_y + 1 <= 29) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x][move_land_y + 1]->color;
						 cube2[move_land_x][move_land_y + 1]->color = Color(1,0,0);
						 move_land_y++;
					 }
				 }

				 if(mod == 20) {
					 if(move_land_y + 1 <= 29) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x][move_land_y + 1]->color;
						 cube2[move_land_x][move_land_y + 1]->color = Color(0.3f,0.2f,0.6f);
						 move_land_y++;
					 }
				 }

				 if(mod == 30) {
					 if(xx1 <= 28 && xx2 <= 28 && xx3 <= 28) {
						 casaX[nr_casa] += 50 * sqrt(2) / 2;
						 casaY[nr_casa] -= 50 * 0.408244;

						 xx1 += 1;
						 xx2 += 1;
						 xx3 += 1;
					 }
				 }

				 if(mod == 40) {
					 if(move_land_y + 1 <= 29) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x][move_land_y + 1]->color;
						 cube2[move_land_x][move_land_y + 1]->color = Color(1,0,0);
						 move_land_y++;
					 }
				 }
			}
		break;

		case 'j' : 
			{ 
				 if(mod == 10) {
					 if(move_land_y - 1 >= 0) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x][move_land_y - 1]->color;
						 cube2[move_land_x][move_land_y - 1]->color = Color(1,0,0);
						 move_land_y--;
					 }
				 }

				 if(mod == 20) {
					 if(move_land_y - 1 >= 0) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x][move_land_y - 1]->color;
						 cube2[move_land_x][move_land_y - 1]->color = Color(0.3f,0.2f,0.6f);
						 move_land_y--;
					 }
				 }

				 if(mod == 30) {
					 if(xx1 >= 1 && xx2 >= 1 && xx3 >= 1) {
						 casaX[nr_casa] -= 50 * sqrt(2) / 2;
						 casaY[nr_casa] += 50 * 0.408244;

						 xx1 -= 1;
						 xx2 -= 1;
						 xx3 -= 1;
					 }
				 }

				 if(mod == 40) {
					 if(move_land_y - 1 >= 0) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x][move_land_y - 1]->color;
						 cube2[move_land_x][move_land_y - 1]->color = Color(1,0,0);
						 move_land_y--;
					 }
				 }
			}
		break;

		case 'k' : 
			{ 
				 if(mod == 10) {
					 if(move_land_x - 1 >= 0) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x - 1][move_land_y]->color;
						 cube2[move_land_x - 1][move_land_y]->color = Color(1,0,0);
						 move_land_x--;
					 }
				 }

				 if(mod == 20) {
					 if(move_land_x - 1 >= 0) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x - 1][move_land_y]->color;
						 cube2[move_land_x - 1][move_land_y]->color = Color(0.3f,0.2f,0.6f);
						 move_land_x--;
					 }
				 }

				 if(mod == 30) {
					 if(yy1 >= 1 && yy2 >= 1 && yy3 >= 1) {
						 casaX[nr_casa] -= 50 * sqrt(2) / 2;
						 casaY[nr_casa] -= 50 * 0.408244;
	 
						 yy1 -= 1;
						 yy2 -= 1;
						 yy3 -= 1;
					 }
				 }

				 if(mod == 40) {
					 if(move_land_x - 1 >= 0) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x - 1][move_land_y]->color;
						 cube2[move_land_x - 1][move_land_y]->color = Color(1,0,0);
						 move_land_x--;
					 }
				 }

			}
		break;

		case 'i' : 
			{ 
				 if(mod == 10) {
					 if(move_land_x + 1 <= 29) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x + 1][move_land_y]->color;
						 cube2[move_land_x + 1][move_land_y]->color = Color(1,0,0);
						 move_land_x++;
					 }
				 }

				 if(mod == 20) {
					 if(move_land_x + 1 <= 29) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x + 1][move_land_y]->color;
						 cube2[move_land_x + 1][move_land_y]->color = Color(0.3f,0.2f,0.6f);
						 move_land_x++;
					 }
				 }

				 if(mod == 30) {
					 if(yy1 <= 28 && yy2 <= 28 && yy3 <= 28) {
						 casaX[nr_casa] += 50 * sqrt(2) / 2;
						 casaY[nr_casa] += 50 * 0.408244;

						 yy1 += 1;
						 yy2 += 1;
						 yy3 += 1;
					 }
				 }

				 if(mod == 40) {
					if(move_land_x + 1 <= 29) {
						 cube2[move_land_x][move_land_y]->color = color_prev;
						 color_prev = cube2[move_land_x + 1][move_land_y]->color;
						 cube2[move_land_x + 1][move_land_y]->color = Color(1,0,0);
						 move_land_x++;
					 }			 
				 }
			}
		break;


		/* Taste alegere tip teren */
		case 'b' :
			{
				if(mod == 11) {
					cube2[move_land_x][move_land_y]->color = TERRAIN;
					color_prev = TERRAIN;
					construibil[move_land_x][move_land_y] = 0;
				}
			}
		break;

		case 'n' :
			{
				if(mod == 11) {
					cube2[move_land_x][move_land_y]->color = WATER;
					color_prev = WATER;
					construibil[move_land_x][move_land_y] = 3;
				}
			}
		break;

		case 'm' :
			{
				if(mod == 11) {
					cube2[move_land_x][move_land_y]->color = GRASS;
					color_prev = GRASS;
					construibil[move_land_x][move_land_y] = 0;
				}
			}
		break;

		case ',' :
			{
				if(mod == 11) {
					for(i = 0; i < 30; i++) {
						for(j = 0; j < 30; j++) {
							removeObject3D_from_Visual2D(cube[i][j], v2d1);
							removeObject3D_from_Visual2D(cube2[i][j], v2d1);
						}
					}
							
					
					vertices6[contor_relief].push_back(new Point3D(50*move_land_x,0,50*move_land_y));
					vertices6[contor_relief].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y));
					vertices6[contor_relief].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+50));
					vertices6[contor_relief].push_back(new Point3D(50*move_land_x,0,50*move_land_y+50));
	
					vertices6[contor_relief].push_back(new Point3D(50*move_land_x+23,100,50*move_land_y+23));
					vertices6[contor_relief].push_back(new Point3D(50*move_land_x+27,100,50*move_land_y+23));
					vertices6[contor_relief].push_back(new Point3D(50*move_land_x+27,100,50*move_land_y+27));
					vertices6[contor_relief].push_back(new Point3D(50*move_land_x+23,100,50*move_land_y+27));

					relief[contor_relief] = new Object3D(vertices6[contor_relief], faces, Color(0, 0.8f, 0), true);
					addObject3D_to_Visual2D(relief[contor_relief],v2d1);
					objects.push_back(relief[contor_relief]);
					contor_relief++;

							
					for(i = 0; i < 30; i++) {
						for(j = 0; j < 30; j++) {
							addObject3D_to_Visual2D(cube[i][j],v2d1);
							addObject3D_to_Visual2D(cube2[i][j],v2d1);
						}
					}
				
					cube2[move_land_x][move_land_y]->color = WATER;
					color_prev = WATER;
					construibil[move_land_x][move_land_y] = 3;
				}

			}
		break;
		

		/* Space */
		case 32 :
			{
				if(mod == 10) {
					mod = 11;
					cube2[move_land_x][move_land_y]->color = SELECTED;
				}

				if(mod == 20) {
					mod = 21;
					
					if (move_land_x >= 4 && move_land_x <= 25 && move_land_y >= 4 && move_land_y <= 25) {
						for(i = move_land_x - 4; i <= move_land_x + 4; i++) {
							for(j = move_land_y - 4; j <= move_land_y + 4; j++) {
								if(construibil[i][j] == 10) {
									suprapunere++;
								}
							}
						}
					}


					if((color_prev.r == WATER.r && color_prev.g == WATER.g, color_prev.b == WATER.b)
						|| (move_land_x  < 4 || move_land_x >= 26 || move_land_y < 4 || move_land_y >= 26)
						|| suprapunere != 0) {
						cube2[move_land_x][move_land_y]->color = BLACK;
					} else {
						cube2[move_land_x][move_land_y]->color = SELECTED;
						for(i = move_land_x - 4; i <= move_land_x + 4; i++) {
							for(j = move_land_y - 4; j <= move_land_y + 4; j++) {
								cube2[i][j]->color.r += 0.2f;
							}
						}
					}
				}

				if(mod == 40) {
					if(construibil[move_land_x][move_land_y] == 10 && (construibil[move_land_x - 1][move_land_y] == 2 || construibil[move_land_x + 1][move_land_y] == 2 ||construibil[move_land_x][move_land_y + 1] == 2 ||construibil[move_land_x][move_land_y - 1]  == 2)) {
						mod = 41;

						for(i = 0; i < 30; i++) {
							for(j = 0; j < 30; j++) {
								removeObject3D_from_Visual2D(cube[i][j], v2d1);
								removeObject3D_from_Visual2D(cube2[i][j], v2d1);
							}
						}

						vertices4[contor_drum].push_back(new Point3D(50*move_land_x,0,50*move_land_y));
						vertices4[contor_drum].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y));
						vertices4[contor_drum].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+50));
						vertices4[contor_drum].push_back(new Point3D(50*move_land_x,0,50*move_land_y+50));
	
						vertices4[contor_drum].push_back(new Point3D(50*move_land_x,5,50*move_land_y));
						vertices4[contor_drum].push_back(new Point3D(50*move_land_x+50,5,50*move_land_y));
						vertices4[contor_drum].push_back(new Point3D(50*move_land_x+50,5,50*move_land_y+50));
						vertices4[contor_drum].push_back(new Point3D(50*move_land_x,5,50*move_land_y+50));

						drum[contor_drum] = new Object3D(vertices4[contor_drum], faces, Color(1, 1, 1), true);
						addObject3D_to_Visual2D(drum[contor_drum],v2d1);
						objects.push_back(drum[contor_drum]);
						contor_drum++;

						for(i = 0; i < 30; i++) {
							for(j = 0; j < 30; j++) {
								addObject3D_to_Visual2D(cube[i][j],v2d1);
								addObject3D_to_Visual2D(cube2[i][j],v2d1);
							}
						}

						construibil[move_land_x][move_land_y] = 2;

						if(construibil[move_land_x][move_land_y - 1] == 5) {

							for(i = 0; i < 30; i++) {
								for(j = 0; j < 30; j++) {
									removeObject3D_from_Visual2D(cube[i][j], v2d1);
									removeObject3D_from_Visual2D(cube2[i][j], v2d1);
								}
							}

							for(i = 0; i < contor_house; i++) {
								removeObject3D_from_Visual2D(house[i], v2d1);
							}
							
							for(i = 0; i < contor_drum; i++) {
								removeObject3D_from_Visual2D(drum[i], v2d1);
							}
					
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,0,50*move_land_y-50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y-50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,0,50*move_land_y));
	
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,50,50*move_land_y-50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y-50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,50,50*move_land_y));

							mark[contor_mark] = new Object3D(vertices5[contor_mark], faces, Color(0.7f,0.2f,0.7f), true);
							addObject3D_to_Visual2D(mark[contor_mark],v2d1);
							objects.push_back(mark[contor_mark]);
							contor_mark++;

							for(i = 0; i < contor_house; i++) {
								addObject3D_to_Visual2D(house[i], v2d1);
							}

							for(i = 0; i < contor_drum; i++) {
								addObject3D_to_Visual2D(drum[i], v2d1);
							}
							
							for(i = 0; i < 30; i++) {
								for(j = 0; j < 30; j++) {
									addObject3D_to_Visual2D(cube[i][j],v2d1);
									addObject3D_to_Visual2D(cube2[i][j],v2d1);
								}
							}


						}



						if(construibil[move_land_x][move_land_y + 1] == 5) {

							for(i = 0; i < 30; i++) {
								for(j = 0; j < 30; j++) {
									removeObject3D_from_Visual2D(cube[i][j], v2d1);
									removeObject3D_from_Visual2D(cube2[i][j], v2d1);
								}
							}

							for(i = 0; i < contor_house; i++) {
								removeObject3D_from_Visual2D(house[i], v2d1);
							}

							for(i = 0; i < contor_drum; i++) {
								removeObject3D_from_Visual2D(drum[i], v2d1);
							}

							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,0,50*move_land_y+50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+100));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,0,50*move_land_y+100));
	
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,50,50*move_land_y+50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y+50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y+100));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,50,50*move_land_y+100));

							mark[contor_mark] = new Object3D(vertices5[contor_mark], faces, Color(0.7f,0.2f,0.7f), true);
							addObject3D_to_Visual2D(mark[contor_mark],v2d1);
							objects.push_back(mark[contor_mark]);
							contor_mark++;

							for(i = 0; i < contor_house; i++) {
								addObject3D_to_Visual2D(house[i], v2d1);
							}

							for(i = 0; i < contor_drum; i++) {
								addObject3D_to_Visual2D(drum[i], v2d1);
							}
							
							for(i = 0; i < 30; i++) {
								for(j = 0; j < 30; j++) {
									addObject3D_to_Visual2D(cube[i][j],v2d1);
									addObject3D_to_Visual2D(cube2[i][j],v2d1);
								}
							}


						}



						if(construibil[move_land_x - 1][move_land_y] == 5) {

							for(i = 0; i < 30; i++) {
								for(j = 0; j < 30; j++) {
									removeObject3D_from_Visual2D(cube[i][j], v2d1);
									removeObject3D_from_Visual2D(cube2[i][j], v2d1);
								}
							}

							for(i = 0; i < contor_house; i++) {
								removeObject3D_from_Visual2D(house[i], v2d1);
							}

							for(i = 0; i < contor_drum; i++) {
								removeObject3D_from_Visual2D(drum[i], v2d1);
							}

							vertices5[contor_mark].push_back(new Point3D(50*move_land_x-50,0,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,0,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,0,50*move_land_y+50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x-50,0,50*move_land_y+50));
	
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x-50,50,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,50,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x,50,50*move_land_y+50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x-50,50,50*move_land_y+50));

							mark[contor_mark] = new Object3D(vertices5[contor_mark], faces, Color(0.7f,0.2f,0.7f), true);
							addObject3D_to_Visual2D(mark[contor_mark],v2d1);
							objects.push_back(mark[contor_mark]);
							contor_mark++;

							for(i = 0; i < contor_house; i++) {
								addObject3D_to_Visual2D(house[i], v2d1);
							}

							for(i = 0; i < contor_drum; i++) {
								addObject3D_to_Visual2D(drum[i], v2d1);
							}
							
							for(i = 0; i < 30; i++) {
								for(j = 0; j < 30; j++) {
									addObject3D_to_Visual2D(cube[i][j],v2d1);
									addObject3D_to_Visual2D(cube2[i][j],v2d1);
								}
							}

						}


						if(construibil[move_land_x + 1][move_land_y] == 5) {

							for(i = 0; i < 30; i++) {
								for(j = 0; j < 30; j++) {
									removeObject3D_from_Visual2D(cube[i][j], v2d1);
									removeObject3D_from_Visual2D(cube2[i][j], v2d1);
								}
							}

							for(i = 0; i < contor_house; i++) {
								removeObject3D_from_Visual2D(house[i], v2d1);
							}

							for(i = 0; i < contor_drum; i++) {
								removeObject3D_from_Visual2D(drum[i], v2d1);
							}

							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+100,0,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+100,0,50*move_land_y +50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+50));
	
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+100,50,50*move_land_y));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+100,50,50*move_land_y+50));
							vertices5[contor_mark].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y+50));

							mark[contor_mark] = new Object3D(vertices5[contor_mark], faces, Color(0.7f,0.2f,0.7f), true);
							addObject3D_to_Visual2D(mark[contor_mark],v2d1);
							objects.push_back(mark[contor_mark]);
							contor_mark++;

							for(i = 0; i < contor_house; i++) {
								addObject3D_to_Visual2D(house[i], v2d1);
							}

							for(i = 0; i < contor_drum; i++) {
								addObject3D_to_Visual2D(drum[i], v2d1);
							}
							
							for(i = 0; i < 30; i++) {
								for(j = 0; j < 30; j++) {
									addObject3D_to_Visual2D(cube[i][j],v2d1);
									addObject3D_to_Visual2D(cube2[i][j],v2d1);
								}
							}

						}

					}
				}

			}
		break;

		case 'f':
			{
				if(mod == 21 && !(cube2[move_land_x][move_land_y]->color.r == 0 && cube2[move_land_x][move_land_y]->color.g == 0 &&cube2[move_land_x][move_land_y]->color.b == 0)) {
					mod = 22;

					for(i = 0; i < 30; i++) {
						for(j = 0; j < 30; j++) {
							removeObject3D_from_Visual2D(cube[i][j], v2d1);
							removeObject3D_from_Visual2D(cube2[i][j], v2d1);
						}
					}

					for(i = 0; i < contor_relief; i++) {
						removeObject3D_from_Visual2D(relief[i], v2d1);
					}

					vertices2[contor_piata].push_back(new Point3D(50*move_land_x,0,50*move_land_y));
					vertices2[contor_piata].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y));
					vertices2[contor_piata].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+50));
					vertices2[contor_piata].push_back(new Point3D(50*move_land_x,0,50*move_land_y+50));
	
					vertices2[contor_piata].push_back(new Point3D(50*move_land_x,100,50*move_land_y));
					vertices2[contor_piata].push_back(new Point3D(50*move_land_x+50,100,50*move_land_y));
					vertices2[contor_piata].push_back(new Point3D(50*move_land_x+50,100,50*move_land_y+50));
					vertices2[contor_piata].push_back(new Point3D(50*move_land_x,100,50*move_land_y+50));

					piata[contor_piata] = new Object3D(vertices2[contor_piata], faces, Color(0.4f,0.4f,0.4f), true);
					addObject3D_to_Visual2D(piata[contor_piata],v2d1);
					objects.push_back(piata[contor_piata]);
					contor_piata++;

					for(i = 0; i < contor_relief; i++) {
						addObject3D_to_Visual2D(relief[i], v2d1);
					}

					for(i = 0; i < 30; i++) {
						for(j = 0; j < 30; j++) {
							addObject3D_to_Visual2D(cube[i][j],v2d1);
							addObject3D_to_Visual2D(cube2[i][j],v2d1);
						}
					}

					for(i = move_land_x - 4; i <= move_land_x + 4; i++) {
						for(j = move_land_y - 4; j <= move_land_y + 4; j++) {
							if(construibil[i][j] != 3) {
								construibil[i][j] = 10;
							}
							construibil[move_land_x][move_land_y] = 2;
						}
					}
				}
				

				if(mod == 30) {

					if(construibil[yy1][xx1] == 10 && construibil[yy2][xx2] == 10  && construibil[yy3][xx3] == 10) {
						mod = 31;
						nr_casa++;

						construibil[yy1][xx1] = 5;
						construibil[yy2][xx2] = 5;
						construibil[yy3][xx3] = 5;

						house[contor_house++] = casa[contor_casa - 1];
						house[contor_house++] = casa[contor_casa - 2];
						house[contor_house++] = casa[contor_casa - 3];
					}

				}
			
			}
		break;



		/* Taste alegere mod editare */
		case '1' : 
			{	
				if(mod == 0) {
					mod = 10;
					color_prev = cube2[15][15]->color;
					cube2[15][15]->color = Color(1,0,0);
				}
			}
		break;

		case '2' : 
			{ 
				 if(mod == 0) {
					 mod = 20;
					 color_prev = cube2[15][15]->color;
					 cube2[15][15]->color = Color(0.3f,0.2f,0.6f);
				 }
			}
		break;

		case '3' : 
			{ 
				 if(mod == 0) {
					 mod = 30;

					 xx1 = 15;
					 xx2 = 15;
					 xx3 = 16;
					 yy1 = 15;
					 yy2 = 16;
					 yy3 = 15;

					 for(i = 0; i < 30; i++) {
						 for(j = 0; j < 30; j++) {
							 if(construibil[i][j] == 10) {
								 cube2[i][j]->color.r += 0.2f;
							 }
						 }
					 }


					 /* Stergere */
					 for(i = 0; i < 30; i++) {
						for(j = 0; j < 30; j++) {
							removeObject3D_from_Visual2D(cube[i][j], v2d1);
							removeObject3D_from_Visual2D(cube2[i][j], v2d1);
						}
					}

					 for(i = 0; i < contor_drum; i++) {
						removeObject3D_from_Visual2D(drum[i], v2d1);
					 }

					vertices3[contor_casa].push_back(new Point3D(50*move_land_x,0,50*move_land_y));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+50));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x,0,50*move_land_y+50));
	
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x,50,50*move_land_y));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y+50));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x,50,50*move_land_y+50));

					casa[contor_casa] = new Object3D(vertices3[contor_casa], faces, Color(0.4f,0.4f,0.4f), true);
					addObject3D_to_Visual2D(casa[contor_casa],v2d1);
					objects.push_back(casa[contor_casa]);
					contor_casa++;
					
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x,0,50*move_land_y+50));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+50));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+100));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x,0,50*move_land_y+100));
	
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x,50,50*move_land_y+50));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y+50));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y+100));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x,50,50*move_land_y+100));

					casa[contor_casa] = new Object3D(vertices3[contor_casa], faces, Color(0.4f,0.4f,0.4f), true);
					addObject3D_to_Visual2D(casa[contor_casa],v2d1);
					objects.push_back(casa[contor_casa]);
					contor_casa++;


					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+100,0,50*move_land_y));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+100,0,50*move_land_y+50));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,0,50*move_land_y+50));
	
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+100,50,50*move_land_y));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+100,50,50*move_land_y+50));
					vertices3[contor_casa].push_back(new Point3D(50*move_land_x+50,50,50*move_land_y+50));

					casa[contor_casa] = new Object3D(vertices3[contor_casa], faces, Color(0.4f,0.4f,0.4f), true);
					addObject3D_to_Visual2D(casa[contor_casa],v2d1);
					objects.push_back(casa[contor_casa]);
					contor_casa++;


					/* Readaugare */
					for(i = 0; i < contor_drum; i++) {
						addObject3D_to_Visual2D(drum[i], v2d1);
					 }

					for(i = 0; i < 30; i++) {
						for(j = 0; j < 30; j++) {
							addObject3D_to_Visual2D(cube[i][j],v2d1);
							addObject3D_to_Visual2D(cube2[i][j],v2d1);
						}
					}
				 
				 }
			}
		break;

		case '4' : 
			{ 
				 if(mod == 0) {
					 mod = 40;
					 color_prev = cube2[15][15]->color;
					 cube2[15][15]->color = Color(1, 0, 0);
				 }
			}
		break;


		/* Scroll-ul revine in centrul grid-ului */
		case 'c' : 
			{
				incX = -700.0f, 
				incY = 300.0f;
			}
		break;


		/* Rotatie in sens trigonometric */
		case 't' :
			{
				if(mod == 30) {

					if(xx1 == xx2 && yy1 == yy3 && xx3 > xx2){
						X1[nr_casa] += 50 * sqrt(2) / 2;
						Y1[nr_casa] -= 50 * 0.408244;
						xx1 += 1;

						X3[nr_casa] -= 50 * sqrt(2) / 2;
						Y3[nr_casa] -= 50 * 0.408244;
						yy2 -= 1;

						X2[nr_casa] += 50 * sqrt(2) / 2;
						Y2[nr_casa] += 50 * 0.408244;
						yy3 += 1;

						break;
					}

						
					if(xx3 == xx1 && yy1 == yy2 && xx3 > xx2) {
						X1[nr_casa] += 50 * sqrt(2) / 2;
						Y1[nr_casa] += 50 * 0.408244;
						yy1 += 1;

						X3[nr_casa] += 50 * sqrt(2) / 2;
						Y3[nr_casa] -= 50 * 0.408244;
						xx2 += 1;

						X2[nr_casa] -= 50 * sqrt(2) / 2;
						Y2[nr_casa] += 50 * 0.408244;
						xx3 -= 1;

						break;
					}

					if(yy1 == yy3 && xx2 == xx1 && xx3 < xx2) {
						X1[nr_casa] -= 50 * sqrt(2) / 2;
						Y1[nr_casa] += 50 * 0.408244;
						xx1 -= 1;

						X3[nr_casa] += 50 * sqrt(2) / 2;
						Y3[nr_casa] += 50 * 0.408244;
						yy2 += 1;

						X2[nr_casa] -= 50 * sqrt(2) / 2;
						Y2[nr_casa] -= 50 * 0.408244;
						yy3 -= 1;

						break;
					}

					if(yy1 == yy2 && xx1 == xx3 && xx3 < xx2) {
						X1[nr_casa] -= 50 * sqrt(2) / 2;
						Y1[nr_casa] -= 50 * 0.408244;
						yy1 -= 1;

						X3[nr_casa] -= 50 * sqrt(2) / 2;
						Y3[nr_casa] += 50 * 0.408244;
						xx2 -= 1;

						X2[nr_casa] += 50 * sqrt(2) / 2;
						Y2[nr_casa] -= 50 * 0.408244;
						xx3 += 1;

						break;
					}
				}
			}
		break;


		/* Rotatie in sens anti-trigonometric */
		case 'y' :
			{
				if(mod == 30) {
	
					if(xx1 == xx2 && yy1 == yy3 && xx3 > xx2){
						X1[nr_casa] += 50 * sqrt(2) / 2;
						Y1[nr_casa] += 50 * 0.408244;
						yy1 += 1;

						X3[nr_casa] += 50 * sqrt(2) / 2;
						Y3[nr_casa] -= 50 * 0.408244;
						xx2 += 1;

						X2[nr_casa] -= 50 * sqrt(2) / 2;
						Y2[nr_casa] += 50 * 0.408244;
						xx3 -= 1;
						
						break;
					}
						
					if(xx1 == xx3 && yy1 == yy2 && xx3 < xx2) {
						X1[nr_casa] += 50 * sqrt(2) / 2;
						Y1[nr_casa] -= 50 * 0.408244;
						xx1 += 1;

						X3[nr_casa] -= 50 * sqrt(2) / 2;
						Y3[nr_casa] -= 50 * 0.408244;
						yy2 -= 1;

						X2[nr_casa] += 50 * sqrt(2) / 2;
						Y2[nr_casa] += 50 * 0.408244;
						yy3 += 1;

						break;
					}

					if(xx1 == xx2 && yy1 == yy3 && xx3 < xx2) {
						X1[nr_casa] -= 50 * sqrt(2) / 2;
						Y1[nr_casa] -= 50 * 0.408244;
						yy1 -= 1;

						X3[nr_casa] -= 50 * sqrt(2) / 2;
						Y3[nr_casa] += 50 * 0.408244;
						xx2 -= 1;

						X2[nr_casa] += 50 * sqrt(2) / 2;
						Y2[nr_casa] -= 50 * 0.408244;
						xx3 += 1;

						break;
					}

					if(yy1 == yy2 && xx1 == xx3 && xx3 > xx2) {
						X1[nr_casa] -= 50 * sqrt(2) / 2;
						Y1[nr_casa] += 50 * 0.408244;
						xx1 -= 1;

						X3[nr_casa] += 50 * sqrt(2) / 2;
						Y3[nr_casa] += 50 * 0.408244;
						yy2 += 1;

						X2[nr_casa] -= 50 * sqrt(2) / 2;
						Y2[nr_casa] -= 50 * 0.408244;
						yy3 -= 1;

						break;
					}
				}
			}
		break;
	
		/* Tasta adaugare random de teren la inceputul jocului, inainte de a adauga vreun obiect */
		case 'r' :
			{
				if(contor_piata == 0 && ok == 0 && contor_relief == 0) {
					srand(time(NULL));
					ok = 1;
					for(i = 0; i < 30; i++) {
						for(j = 0; j < 30; j++) {
							r = rand()%15;
							if(r == 0) {
								cube2[i][j]->color = WATER;
								construibil[i][j] = 3;
							} else {
								if(r == 1) {
									cube2[i][j]->color = GRASS;
								} else {
									cube2[i][j]->color = TERRAIN;
								}
							}
						}
					}
				}
			}
			break;


	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 800, 600, 0, 0, "Laborator EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}