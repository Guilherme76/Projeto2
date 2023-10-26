#include <GL/glut.h>

// Variáveis globais
GLfloat angle, fAspect;

// Inicializa parâmetros de rendering
void Init()
{
    // Configuração da luz e do material
    GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};   // "cor"
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
    GLfloat posicaoLuz[4] = {50.0, 50.0, 50.0, 1.0};

    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 60;

    // Especifica que a cor de fundo da janela será preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Define a refletência do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    // Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);

    angle = 45;
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(angle, fAspect, 0.4, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w / (GLfloat)h;
    EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
        {
            if (angle >= 10) angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)
        {
            if (angle <= 130) angle += 5;
        }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

void Display()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; // Tempo em segundos
    const double a = t * 90.0; // Um ciclo completo de rotação a cada 4 segundos (90 graus por segundo)

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int viewportWidth = windowWidth / 2;
    int viewportHeight = windowHeight / 2;

    // Configura viewport para a vista principal
    glViewport(0, 0, windowWidth, windowHeight);

    // Define a visualização principal
    EspecificaParametrosVisualizacao();

    // Desenha o bule no canto superior esquerdo
    glViewport(0, windowHeight / 2, viewportWidth, viewportHeight);
    glLoadIdentity();
    gluLookAt(0, 0, 250, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
    //glRotated(a, 0, 1, 0); // Aplica a rotação em torno do eixo y
    glColor3f(0.f, 0.f, 1.f);
    glutSolidTeapot(50.0f);
    glPopMatrix();

    // Desenha o bule no canto superior direito
    glViewport(viewportWidth, windowHeight / 2, viewportWidth, viewportHeight);
    glLoadIdentity();
    gluLookAt(250, 30, 0, 0, 0, 0, 0, 1, 0);
    //glRotated(a, 0, 1, 0); // Aplica a rotação em torno do eixo y
    glColor3f(0.f, 0.f, 1.f);
    glutSolidTeapot(50.0f);

    // Desenha o bule no canto inferior esquerdo
    glViewport(0, 0, viewportWidth, viewportHeight);
    glLoadIdentity();
    gluLookAt(0, 250, 0, 0, 0, 0, 0, 0, -1);
    //glRotated(a, 0, 1, 0); // Aplica a rotação em torno do eixo y
    glColor3f(0.f, 0.f, 1.f);
    glutSolidTeapot(50.0f);

    // Desenha o bule no canto inferior direito
    glViewport(viewportWidth, 0, viewportWidth, viewportHeight);
    glLoadIdentity();
    gluLookAt(100, 120, 350, 0, 0, 0, 0, 1, 0);
    glRotated(a, 0, 1, 0); // Aplica a rotação em torno do eixo y
    glColor3f(0.f, 0.f, 1.f);
    glutSolidTeapot(50.0f);

    glutSwapBuffers();
    glutPostRedisplay();
}


// Programa Principal
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Display);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);
    Init();
    glutMainLoop();
    return 0;
}
