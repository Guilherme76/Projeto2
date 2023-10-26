#include <GL/glut.h>

GLfloat objectPositionX = 1.5f;
GLfloat objectPositionY = -0.3f;
GLfloat objectPositionZ = 1.0f;

GLfloat angle = 45.0f;

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Define a cor de fundo
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade

    float globalAmb[] = {0.9f, 0.9f, 0.9f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

    // Configuração da perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, 1.0f, 0.1f, 100.0f); // Campo de visão, Razão de aspecto, Plano próximo, Plano distante

    // Configuração da câmera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4, 3.7, 7.7, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Habilita luz e iluminação de ambos os lados das faces
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float light0[4][4] = {
                {0.1f, 0.1f, 0.1f, 1.0f},
                {0.8f, 0.8f, 0.8f, 1.0f},
                {1.f, 1.f, 1.f, 1.f},
                {-1.f, 7.f, -5.f, 1.f}
    };

    glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &light0[3][0]);

    glEnable(GL_LIGHT1);
}

void EspecificaParametrosVisualizacao() {
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(angle, 1.0f, 0.1f, 100.f);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(4, 3.7, 7.7, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void GerenciaMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Zoom-in
        if (angle >= 10) angle -= 5;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Zoom-out
        if (angle <= 130) angle += 5;
    }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    // Manipula eventos de teclas especiais (setas)
    switch (key) {
        case GLUT_KEY_UP:
            // Tecla de seta para cima - move o objeto para cima
            objectPositionY += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            // Tecla de seta para baixo - move o objeto para baixo, mas verifica se está acima do limite mínimo
            if (objectPositionY > -0.5f) {
                objectPositionY -= 0.1f;
            }
            break;
        case GLUT_KEY_LEFT:
            // Tecla de seta para a esquerda - move o objeto para a esquerda
            if (objectPositionX > -1.7f) {
                objectPositionX -= 0.1f;
            }
            break;
        case GLUT_KEY_RIGHT:
            // Tecla de seta para a direita - move o objeto para a direita
            objectPositionX += 0.1f;
            break;
        case GLUT_KEY_PAGE_UP:
            // Tecla de Page Up - move o objeto para frente no eixo Z
            if (objectPositionZ > -2.f) {
                objectPositionZ -= 0.1f;
            }
            break;
        case GLUT_KEY_PAGE_DOWN:
            // Tecla de Page Down - move o objeto para trás no eixo Z
            objectPositionZ += 0.1f;
            break;
    }
    glutPostRedisplay(); // Marca a janela para redesenho
}

void display() {

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Limpa o buffer de cor e de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configura normais para as faces dos cubos
    glEnable(GL_NORMALIZE);

    // Desenha os cubos com normais
    GLfloat materialAmbient4[] = {0.2f, 0.0f, 0.0f, 1.0f}; // Azul
    GLfloat materialDiffuse4[] = {1.0f, 0.0f, 0.0f, 1.0f}; // Azul
    GLfloat materialSpecular4[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Branco
    GLfloat shininess4 = 50.0f; // Brilho do material

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient4);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse4);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular4);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess4);

    // Desenha o primeiro cubo
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(5, 0.10, 5);
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
    glNormal3f(0, 0, -1);
    glutSolidCube(1);
    glPopMatrix();

    // Desenha o segundo cubo
    glPushMatrix();
    glTranslatef(-0.40, -0.77, -3.5);
    glScalef(-5.5, 1.35, 0.10);
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
    glNormal3f(0, 0, 1);
    glutSolidCube(1);
    glPopMatrix();

    // Desenha o terceiro cubo
    glPushMatrix();
    glTranslatef(-2.52, -0.4, 0);
    glScalef(0.10, 1.25, -5);
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
    glNormal3f(-1, 0, 0);
    glutSolidCube(1);
    glPopMatrix();

    // Desenha o torus verde
    glPushMatrix();
    glTranslatef(objectPositionX, objectPositionY, objectPositionZ);
    glRotatef(90, 1.0, 0.0, 0.0); // Rotação de 90 graus para deitar o torus

    GLfloat materialAmbient2[] = {0.0f, 0.2f, 0.0f, 1.0f}; // Verde
    GLfloat materialDiffuse2[] = {0.0f, 1.0f, 0.0f, 1.0f}; // Verde
    GLfloat materialSpecular2[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Branco
    GLfloat shininess2 = 100.0f; // Brilho do material

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular2);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess2);

    glColor3f(0.0f, 1.0f, 0.0f); // Cor verde
    glutSolidTorus(0.18, 0.7, 40, 40); // Raio do tubo, raio do torus, divisões no tubo, divisões no torus
    glPopMatrix();

    // Desenha o bule azul
    glPushMatrix();
    glRotatef(45.f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-2.f, 0.0f, 0.5f);

    GLfloat materialAmbient1[] = {0.0f, 0.0f, 0.2f, 1.0f}; // Azul
    GLfloat materialDiffuse1[] = {0.0f, 0.0f, 1.f, 1.0f}; // Azul
    GLfloat materialSpecular1[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Branco
    GLfloat shininess1 = 50.0f; // Brilho do material

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular1);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess1);

    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul
    glutSolidTeapot(0.7); // Desenha o bule
    glPopMatrix();

    // Desenha a esfera amarela
    glPushMatrix();
    glTranslatef(-1.1, 0.0, -0.6);

    GLfloat materialAmbient3[] = {0.2f, 0.2f, 0.0f, 1.0f}; // Amarelo
    GLfloat materialDiffuse3[] = {1.0f, 1.0f, 0.0f, 1.0f}; // Amarelo
    GLfloat materialSpecular3[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Branco
    GLfloat shininess3 = 100.0f; // Brilho do material

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular3);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess3);

    glColor3f(1.0f, 1.0f, 0.0f); // Cor amarela
    glutSolidSphere(0.7, 20, 20); // Raio 1.0, divisões 20, 20
    glPopMatrix();

    // Troca os buffers para exibir a cena renderizada
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inicializa o GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE); // Configura o modo de exibição
    glutInitWindowSize(600, 600); // Configura a largura e altura da janela
    glutCreateWindow("Cena 3d"); // Cria a janela
    init(); // Executa a função de inicialização
    glutDisplayFunc(display); // Registra a função de desenho
    glutSpecialFunc(specialKeys); // Registra a função para teclas especiais
    glutMouseFunc(GerenciaMouse);
    glutMainLoop(); // Entra no loop principal do GLUT
    return 0;
}
