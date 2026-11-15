#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

// Current scene number
int currentScene = 1;

// Character position
float playerX = -0.6f;
float playerY = -0.4f;

// Scene 2 variables
float coinX[5] = { -0.5f, -0.2f, 0.1f, 0.4f, 0.6f };
float coinY[5] = { -0.2f, 0.1f, -0.1f, 0.2f, -0.25f };
bool collected[5] = { false, false, false, false, false };
int score = 0;

// Scene 3 variables
float angle3 = 0.0f;
float moveX3 = -0.8f;
float scaleValue3 = 1.0f;
bool grow3 = true;

// Scene 4 colors
float red = 1.0f;
float green = 0.5f;
float blue = 0.0f;

// Function declarations
void display();
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void mouse(int button, int state, int x, int y);

void scene1();
void scene2();
void scene3();
void scene4();

void updateScene3(int value);

void drawCircle(float cx, float cy, float r);
void drawRectangle(float x1, float y1, float x2, float y2);
void drawPlayer(float x, float y);
void drawFriend(float x, float y);
void drawText(float x, float y, const char* text);
void drawStar(float x, float y);

// Draw circle
void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i++)
    {
        float angle = i * 3.14159f / 180;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }

    glEnd();
}

// Draw rectangle
void drawRectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_POLYGON);

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);

    glEnd();
}

// Draw text
void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

// Draw star
void drawStar(float x, float y)
{
    glColor3f(1.0f, 0.9f, 0.0f);

    glBegin(GL_TRIANGLES);

    glVertex2f(x, y + 0.06f);
    glVertex2f(x - 0.04f, y - 0.03f);
    glVertex2f(x + 0.04f, y - 0.03f);

    glVertex2f(x, y - 0.06f);
    glVertex2f(x - 0.04f, y + 0.03f);
    glVertex2f(x + 0.04f, y + 0.03f);

    glEnd();
}

// Draw player
void drawPlayer(float x, float y)
{
    // Body
    glColor3f(0.2f, 0.4f, 1.0f);
    drawRectangle(x - 0.04f, y - 0.15f, x + 0.04f, y);

    // Head
    glColor3f(1.0f, 0.8f, 0.6f);
    drawCircle(x, y + 0.06f, 0.06f);

    // Eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x - 0.02f, y + 0.08f, 0.008f);
    drawCircle(x + 0.02f, y + 0.08f, 0.008f);

    // Smile
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.025f, y + 0.04f);
    glVertex2f(x, y + 0.025f);
    glVertex2f(x + 0.025f, y + 0.04f);
    glEnd();

    // Legs
    glColor3f(0.1f, 0.1f, 0.1f);
    drawRectangle(x - 0.035f, y - 0.25f, x - 0.005f, y - 0.15f);
    drawRectangle(x + 0.005f, y - 0.25f, x + 0.035f, y - 0.15f);
}

// Draw friend
void drawFriend(float x, float y)
{
    // Body
    glColor3f(1.0f, 0.3f, 0.6f);
    drawRectangle(x - 0.04f, y - 0.15f, x + 0.04f, y);

    // Head
    glColor3f(1.0f, 0.8f, 0.6f);
    drawCircle(x, y + 0.06f, 0.06f);

    // Eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x - 0.02f, y + 0.08f, 0.008f);
    drawCircle(x + 0.02f, y + 0.08f, 0.008f);

    // Smile
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.025f, y + 0.04f);
    glVertex2f(x, y + 0.025f);
    glVertex2f(x + 0.025f, y + 0.04f);
    glEnd();

    // Legs
    glColor3f(0.1f, 0.1f, 0.1f);
    drawRectangle(x - 0.035f, y - 0.25f, x - 0.005f, y - 0.15f);
    drawRectangle(x + 0.005f, y - 0.25f, x + 0.035f, y - 0.15f);
}

// Scene 1
void scene1()
{
    // Sky
    glColor3f(0.6f, 0.85f, 1.0f);
    drawRectangle(-1.0f, -1.0f, 1.0f, 1.0f);

    // Ground
    glColor3f(0.3f, 0.8f, 0.3f);
    drawRectangle(-1.0f, -1.0f, 1.0f, -0.45f);

    // Road
    glColor3f(0.25f, 0.25f, 0.25f);
    drawRectangle(-1.0f, -0.75f, 1.0f, -0.55f);

    // Sun
    glColor3f(1.0f, 0.9f, 0.0f);
    drawCircle(0.75f, 0.75f, 0.12f);

    drawPlayer(playerX, playerY);
    drawFriend(0.35f, -0.35f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.85f, 0.85f, "Scene 1: Small City");
    drawText(-0.85f, 0.75f, "Help your friend in the city!");
    drawText(-0.85f, 0.65f, "Use arrow keys to move.");
    drawText(-0.85f, 0.55f, "Press 2 to continue.");
}

// Scene 2
void scene2()
{
    // Background
    glColor3f(0.7f, 0.9f, 1.0f);
    drawRectangle(-1.0f, -1.0f, 1.0f, 1.0f);

    // Ground
    glColor3f(0.4f, 0.8f, 0.4f);
    drawRectangle(-1.0f, -1.0f, 1.0f, -0.45f);

    drawPlayer(playerX, playerY);
    drawFriend(0.65f, -0.35f);

    for (int i = 0; i < 5; i++)
    {
        if (!collected[i])
        {
            drawStar(coinX[i], coinY[i]);

            if (fabs(playerX - coinX[i]) < 0.09f && fabs(playerY - coinY[i]) < 0.09f)
            {
                collected[i] = true;
                score++;
            }
        }
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.85f, 0.85f, "Scene 2: Collect Stars");
    drawText(-0.85f, 0.75f, "Collect stars to help your friend.");
    drawText(-0.85f, 0.65f, "Move near each star.");

    if (score >= 5)
    {
        drawText(-0.25f, 0.55f, "Challenge Completed!");
        drawText(-0.25f, 0.45f, "Press 3 to continue.");
    }
}

// Scene 3
void scene3()
{
    // Background
    glColor3f(0.05f, 0.05f, 0.15f);
    drawRectangle(-1.0f, -1.0f, 1.0f, 1.0f);

    // Text
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.85f, 0.85f, "Scene 3: Magic Star Effect");
    drawText(-0.85f, 0.75f, "A magical star appears.");
    drawText(-0.85f, 0.65f, "The star moves, rotates, and changes size.");
    drawText(-0.85f, 0.55f, "Press 4 to continue.");

    // Transformations
    glPushMatrix();

    glTranslatef(moveX3, 0.0f, 0.0f);
    glRotatef(angle3, 0.0f, 0.0f, 1.0f);
    glScalef(scaleValue3, scaleValue3, 1.0f);

    drawStar(0.0f, 0.0f);

    glPopMatrix();

    drawText(-0.45f, -0.75f, "Magic Star Effect using transformations.");
}

// Animation for scene 3
void updateScene3(int value)
{
    angle3 += 2.0f;

    moveX3 += 0.01f;

    if (moveX3 > 0.8f)
        moveX3 = -0.8f;

    if (grow3)
        scaleValue3 += 0.01f;
    else
        scaleValue3 -= 0.01f;

    if (scaleValue3 >= 1.4f)
        grow3 = false;

    if (scaleValue3 <= 0.7f)
        grow3 = true;

    glutPostRedisplay();
    glutTimerFunc(16, updateScene3, 0);
}

// Scene 4
void scene4()
{
    // Background
    glColor3f(0.9f, 1.0f, 0.9f);
    drawRectangle(-1.0f, -1.0f, 1.0f, 1.0f);

    drawPlayer(-0.35f, -0.35f);
    drawFriend(0.35f, -0.35f);

    // Gift
    glColor3f(red, green, blue);
    drawRectangle(-0.12f, -0.42f, 0.12f, -0.18f);

    // Ribbon
    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(-0.02f, -0.42f, 0.02f, -0.18f);
    drawRectangle(-0.12f, -0.32f, 0.12f, -0.28f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.85f, 0.85f, "Scene 4: Thank You Gift");
    drawText(-0.85f, 0.75f, "Your friend gives you a gift.");
    drawText(-0.85f, 0.65f, "Make the gift yellow.");
    drawText(-0.85f, 0.55f, "Click mouse to choose the correct color.");

    if (red == 1.0f && green == 1.0f && blue == 0.0f)
    {
        drawText(-0.12f, -0.05f, "Correct!");
    }
}

// Display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentScene == 1)
        scene1();
    else if (currentScene == 2)
        scene2();
    else if (currentScene == 3)
        scene3();
    else if (currentScene == 4)
        scene4();

    glFlush();
}

// Keyboard
void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
        currentScene = 1;
    else if (key == '2')
        currentScene = 2;
    else if (key == '3')
        currentScene = 3;
    else if (key == '4')
        currentScene = 4;
    else if (key == 'r' || key == 'R')
    {
        red = 1.0f;
        green = 0.0f;
        blue = 0.0f;
    }
    else if (key == 'g' || key == 'G')
    {
        red = 0.0f;
        green = 1.0f;
        blue = 0.0f;
    }
    else if (key == 'b' || key == 'B')
    {
        red = 0.0f;
        green = 0.0f;
        blue = 1.0f;
    }

    glutPostRedisplay();
}

// Arrow movement
void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        playerX += 0.05f;
    else if (key == GLUT_KEY_LEFT)
        playerX -= 0.05f;
    else if (key == GLUT_KEY_UP)
        playerY += 0.05f;
    else if (key == GLUT_KEY_DOWN)
        playerY -= 0.05f;

    glutPostRedisplay();
}

// Mouse
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        red = 1.0f;
        green = 1.0f;
        blue = 0.0f;
    }

    glutPostRedisplay();
}

// Main
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Friendship City Game");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);

    glutTimerFunc(16, updateScene3, 0);

    glutMainLoop();

    return 0;
}