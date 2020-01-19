// Hexxagon3DPlayer.cpp: Implementierung der Klasse Hexxagon3DPlayer.
//
//////////////////////////////////////////////////////////////////////

#include "Hexxagon3DPlayer.h"
#include "..\All2DEngine\All2D\All2D_System.h"
//#include <crtdbg.h>

    /*
	 * material properties
	 */
/*
	GLfloat afMaterialAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat afMaterialDiffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat afMaterialSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat afMaterialShininess[] = { 50.0 };


GLfloat RedSurface[]   = { 1.0f, 0.0f, 0.0f, 1.0f};
GLfloat BlueSurface[]  = { 0.0f, 0.0f, 1.0f, 1.0f};

GLfloat RedHLSurface[]   = { 1.0f, 0.8f, 0.0f, 1.0f};
GLfloat BlueHLSurface[]  = { 0.0f, 0.8f, 1.0f, 1.0f};
*/
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Hexxagon3DPlayer::Hexxagon3DPlayer()
{
	//rotateX = 45.0f;
	//rotateY = 45.0f;
	rotateX = 0.0f;
	rotateY = 0.0f;
	hexBoard = 0;
	bInitialized = false;
}

Hexxagon3DPlayer::~Hexxagon3DPlayer()
{
//	if (bInitialized) gluDeleteQuadric(quadObj);

}

void Hexxagon3DPlayer::setBoard(HexxagonBoard* board)
{
	hexBoard = board;
}

void Hexxagon3DPlayer::init3D()
{
    /*
	 * light source
	 */
/*
	GLfloat afLightAmbient[] =  { 0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat afLightDiffuse[] =  { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat afLightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat afLightPosition[] = { 320.0f, 240.0f, 100.0f, 0.0f};
*/
    /*
	 * light model
	 */
/*
	GLfloat afLightModelAmbient[] =  { 0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat afLightModelTwoSide[] = { GL_TRUE };

	GLfloat afDefaultShine[] = { 16.0f,16.0f,16.0f,16.0f };
	GLfloat afHiliteShine[] = { 128.0f,128.0f,128.0f,128.0f };
*/
	// glDisable(GL_TEXTURE_2D);

	/*
	 * set and enable light
	 */
/*
	glLightfv(GL_LIGHT0, GL_AMBIENT, afLightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, afLightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, afLightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, afLightPosition);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, afLightModelAmbient);
	//glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, afLightModelTwoSide);

	glEnable(GL_LIGHT0);


    // draw cone
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);

*/
	bInitialized = true;
}

bool Hexxagon3DPlayer::paint(Image &backBuffer)
{
/*	if (hexBoard!=NULL && All2D_System::getRenderMode()==OPENGL ) {
)
		if (!bInitialized) init3D();

		/*
		 * DEMO rotation effekt
		 * /
		rotateX+=0.5f;
		rotateY+=0.5f;

		if (rotateX>360.0f) rotateX = 0.0f;
		if (rotateY>360.0f) rotateY = 0.0f;



		//glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();									// Reset The View
		//gluLookAt(3.0,3.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);

		//glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glEnable(GL_LIGHTING);



		//glPushMatrix();

			//glViewport(0,0,640,480);
			//glFrustum(4.0,-4.0,4.0,-4.0,1.0,1.0);

			//glTranslated(0.0, 0.0, -5.0);
			//glRotated(rotateX, 1.0, 0.0, 0.0);
			//glRotated(-90, 1.0, 0.0, 0.0);


//			 * DRAW cones on board

			vector<HexxagonStone*> vecStones = hexBoard->getStones();

			HexxagonStone* stone;

			// loop through all stones
			for ( int x=0;x<vecStones.size();x++) {
				stone = vecStones[x];
				int iColor = stone->getColor();
				if ( iColor==HEX_RED_PLAYER || iColor==HEX_BLUE_PLAYER ) {

					Rect r = stone->getPosition();

					//_RPT2( _CRT_WARN, "Reading Stone %d with Color %d", x, iColor);
					//_RPT4( _CRT_WARN, "...has position %d,%d,%d,%d\n", r.x1,r.y1,r.x2,r.y2);


					glPushMatrix();


					//
					// TODO correct translation
					//

						//glTranslated(-2.4f + (r.x1)*0.0076, 2.0f + (r.y1)*-0.0086, 0.0);
						glTranslated(r.x1, r.y1, -90+(r.y1/5.0));
						glRotated(65.0, 1.0, 0.0, 0.0);

						//gluOrtho2D(0,0,640,480);

//	 * set material properties


						if (iColor==HEX_RED_PLAYER) {
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
								(stone->getHoverStatus()) ? RedHLSurface : RedSurface );
						} else {
							glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
								(stone->getHoverStatus()) ? BlueHLSurface : BlueSurface );
						}
	glMaterialfv(GL_FRONT, GL_SPECULAR, afMaterialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, afMaterialShininess);

						//gluQuadricTexture(quadObj,GL_TRUE);
						gluCylinder (quadObj, 24, 0.0, 60, 16, 1);


					glPopMatrix();

					//glTranslated(0.0, (c+1)*-0.4, 0.0);
					//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RedSurface);
					//gluQuadricDrawStyle (quadObj, GLU_FILL);
					//gluQuadricNormals (quadObj, GLU_SMOOTH);
					//gluCylinder (quadObj, 0.2, 0.0, 0.6, 16, 1);

				}
			}
*/
	/*		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RedSurface);
			glBegin(GL_POLYGON);
				glNormal3d(  1.0,  0.0,  0.0);
				glVertex3d(  1.0,  1.0,  1.0);
				glVertex3d(  1.0, -1.0,  1.0);
				glVertex3d(  1.0, -1.0, -1.0);
				glVertex3d(  1.0,  1.0, -1.0);
			glEnd();

			glBegin(GL_POLYGON);
				glNormal3d( -1.0,  0.0,  0.0);
				glVertex3d( -1.0, -1.0,  1.0);
				glVertex3d( -1.0,  1.0,  1.0);
				glVertex3d( -1.0,  1.0, -1.0);
				glVertex3d( -1.0, -1.0, -1.0);
			glEnd();

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GreenSurface);
			glBegin(GL_POLYGON);
				glNormal3d(  0.0,  1.0,  0.0);
				glVertex3d(  1.0,  1.0,  1.0);
				glVertex3d( -1.0,  1.0,  1.0);
				glVertex3d( -1.0,  1.0, -1.0);
				glVertex3d(  1.0,  1.0, -1.0);
			glEnd();

			glBegin(GL_POLYGON);
				glNormal3d(  0.0, -1.0,  0.0);
				glVertex3d( -1.0, -1.0,  1.0);
				glVertex3d(  1.0, -1.0,  1.0);
				glVertex3d(  1.0, -1.0, -1.0);
				glVertex3d( -1.0, -1.0, -1.0);
			glEnd();

			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BlueSurface);
			glBegin(GL_POLYGON);
				glNormal3d(  0.0,  0.0,  1.0);
				glVertex3d(  1.0,  1.0,  1.0);
				glVertex3d( -1.0,  1.0,  1.0);
				glVertex3d( -1.0, -1.0,  1.0);
				glVertex3d(  1.0, -1.0,  1.0);
			glEnd();

			glBegin(GL_POLYGON);
				glNormal3d(  0.0,  0.0, -1.0);
				glVertex3d( -1.0,  1.0, -1.0);
				glVertex3d(  1.0,  1.0, -1.0);
				glVertex3d(  1.0, -1.0, -1.0);
				glVertex3d( -1.0, -1.0, -1.0);
			glEnd();
	*/
		//glPopMatrix();

//		glDisable(GL_LIGHTING);

	//				glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )

//	}
	return true;
}
