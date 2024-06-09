#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Sala
{
    char *descricao;
    struct Sala *norte;
    struct Sala *sul;
    struct Sala *leste;
    struct Sala *oeste;
    int chave;
} Sala;

Sala* criarSala(char *descricao, int chave)
{
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    novaSala->descricao = descricao;
    novaSala->norte = NULL;
    novaSala->sul = NULL;
    novaSala->leste = NULL;
    novaSala->oeste = NULL;
    novaSala->chave = chave;
    return novaSala;
}

void conectarSalas(Sala *origem, Sala *destino, char direcao) 
{
    switch (direcao) 
	{
        case 'N': origem->norte = destino; 
			break;
        case 'S': origem->sul = destino;
			break;
        case 'L': origem->leste = destino;
			break;
        case 'O': origem->oeste = destino;
			break;
    }
}

void exibirDescricao(Sala *sala) 
{
    printf("%s\n", sala->descricao);
}

int verificarChavesColetadas(int chaves[], int tamanho) 
{
    for (int i = 0; i < tamanho; i++) 
	{
        if (chaves[i] == 0) 
		{
            return 0;
        }
    }
    return 1;
}

int main() 
{
    //Cria��o das salas
    Sala *salas[51];
    salas[0] = criarSala("Voce esta na entrada do que parece ser uma grande muralha antiga e robusta. Por algum motivo a sensacao de deja vu eh esmagadora.\nVoce consegue ver o formato de um ser com diversas pernas esculpido em marmore no portal de tal muralha.\nHa somente um caminho: para o NORTE.", 0);
    salas[1] = criarSala("Voce entrou pelo portal e a atmosfera parece estranhamente quieta, e a sensacao de desconforto eh gritante.\nVoce observa uma cidade ao NORTE. \nHa um portal de saida com uma estatua para o SUL\nVoce tambem consegue seguir a muralha pelo LESTE ou pelo OESTE.\n",0);
    salas[2] = criarSala("Voce anda alguns metros seguindo a muralha. \nA medida que voce anda, vai encontrando alguns destrocos do que parecem ser postos de patrulha abandonados.\nEntao voce encontra uma pequena brecha na parede da muralha pelo LESTE.\nOu voce pode voltar pela muralha pelo OESTE", 0);
    salas[3] = criarSala("Voce anda alguns metros seguindo a muralha.\nA medida que voce anda, mais e mais se torna dificil seguir a muralha por conta da quantidade anormal de arvores que vao surgindo.\nVoce entao se ve incapaz de seguir pelo oeste por conta de uma parede de pinheiros a sua frente.\nVoce avista uma catedral pelo NORTE.\nOu voce pode seguir muralha de volta pelo LESTE", 0);
    salas[4] = criarSala("Voce anda por algum tempo. A cada passo dado, seus instintos gritavam para voce retornar, algo naquele local nao parecia certo.\n Apos alguns minutos voce consegue chegar a centro da cidade. Voce procura por algum sinal de vida, mas sem sorte, a cidade estava deserta, como se o povo daquele local tivesse fugido as pressas.\nVoce avista o que parece ser uma biblioteca ao NORTE.\nAo OESTE consegue se ver uma catedral antiga.\nVoce tambem consegue seguir pelo SUL e voltar a entrada da muralha.", 0);
    salas[5] = criarSala("Voce se esgueira e entra pela brecha na parede. \nA atmosfera comeca a ficar cada vez mais claustrofobica. Mais e mais se torna dificil de avancar, e as paredes estao ficando cada vez mais estreitas. \nCom muita dificuldade voce consegue atravessar a grande brecha, mas se ve incapaz de voltar pelo caminho que veio. Dentro da muralha eh extremamente escuro, e a penumbra nao permite que voce enxergue de maneira significativa.\nVoce sente tocar em sua pele uma substancia viscosa, como se fossem grandes quantidades de teia de aranha. \nApesar da dificuldade, voce enxerga um tunel ao qual parece ter sido feito por uma especie de animal pelo SUL", 0);
    salas[6] = criarSala("Voce entra pelo tunel do animal. \nEh dificil se movimentar aqui, mas voce consegue avancar, descendo mais e mais pelo tunel.\nO cheiro dentro do tunel eh insuportavel, como se diversos restos de animais estivessem apodrecendo lentamente.\nVoce escuta um gotejamento estranho e constante, e tal liquido escorre pelo seu pescoco.\nVoce pode seguir pelo tunel em direcao ao LESTE.\nOu voce pode voltar pelo caminho que veio pelo NORTE.", 0);
    salas[7] = criarSala("Voce decide continuar seguindo pelo tunel.\nO caminho esta bloqueado pelo que parecem ser teias de aranha grossas, e a cada passo fica mais dificil de se movimentar. Ate que de repente voce escuta o que parecem ser ALGO se movimentando pelas paredes do grande tunel. \nMas ao andar alguns passos, voce finalmente encontra uma luz pelo que parece ser uma pequena saida.\nVoce pode sair pelo buraco ao OESTE e nao voltar.\n Ou retornar pelo tunel da criatura ao LESTE.", 0);
    salas[8] = criarSala("Voce chega ao que parece ser uma enorme e ameacadora catedral com um estilo gotico.\nEsta nao eh uma catedral comum, mas um monolito de pedra e trevas, um testemunho silencioso de uma era perdida.\nVoce pode adentrar a catedral pelo OESTE.\nIr para o centro da cidade pelo LESTE.\nOu seguir ate a muralha pelo SUL.", 0);
    salas[9] = criarSala("Voce entra na catedral abandonada.\nO som de gotas d'agua ecoa pelo vasto espa�o e a sensacao de solidao agora parecia mais evidente. \nUma enorme estatua da mesma criatura que a do portal abraca um RELOGIO sinistro com suas multiplas patas em cima de um altar onde pareciam ocorrer sacrificios.\nAo analisar a estatua, voce agora consegue identificar que tal criatura parecia possuir a cabeca de um animal semelhante a um bode ou carneiro.\nSeus olhos eram sem vida e ameacadores, como os de uma aranha. \nVoce olha pelo salao, ve varios bancos vazios e diversos simbolos os quais voce nao reconhece escritos nas paredes. \nDe repente um som estrondoroso ecoa pelo salao. Sua atencao retorna ao RELOGIO e voce percebe que o ponteiro comeca a se mover lentamente em direcao ao numero '10' manchado de vermelho. Algo nao parecia certo.\nVoce pode seguir uma porta para o que parece ser o patio pelo OESTE.\nSair da catedral pelo LESTE.\nOu entrar por uma porta atras do altar pelo NORTE.", 0);
    salas[10] = criarSala("Voce entra em uma biblioteca antiga.\nOs livros estao empoeirados e gastos, com excessao de um livro cujo a cor negra como a noite esta disposta em uma mesa no centro da sala.\nHa uma CHAVE em formato de um Querubim em cima do livro aberto, a qual voce imediatamente pega. Voce pode ler uma frase em destaque no livro:\n'GOBIDARST o Puro. GOBIDARST o Justo. Gobidarst o Guardiao. Devemos nossa vida a Ele e somente Ele'\nVoce pode somente sair da biblioteca pelo SUL.", 1);
    salas[11] = criarSala("Voce entra pela porta atras do altar. O corredor � iluminado somente com tochas com fogo azul\nDiversas estatuas humanas em poses como estivessem chorando guiam voce a uma porta adornada no fim do corredor.\nVoce pode entrar na porta adornada pelo NORTE.\nOu voce pode voltar ate a catedral pelo SUL.", 0);
    salas[12] = criarSala("Voce entra em um grande patio onde pareciam ser realizadas as meditacoes dos monges da catedral.\nO campo eh incrivelmente bem cuidado e passa uma estranha sensacao de paz e tranquilidade.\nMas tal tranquilidade eh cortada com um vulto se escondendo nos telhados. Voce decide seguir.\nVoce pode ir para a entrada do Mosteiro pelo SUL\nOu voltar para a catedral pelo LESTE.", 0);
    salas[13] = criarSala("Voce adentra o Mosteiro e avista um grande corredor com as portas escancaradas levando a quartos desarrumados.\nAo andar por alguns metros pelo Mosteiro, um quarto iluminado lhe chama a atencao.\nVoce pode entrar no quarto pelo OESTE\nOu voltar para o patio pelo NORTE.", 0);
    salas[14] = criarSala("Voce entra no que parece ser um vasto templo subterraneo. Duas estatuas de duas mulheres apontam para a esquerda e para a direita.\nO ambiente eh iluminado somente pelas tochas azuis, e diversas pilastras continuam pelo vasto corredor.\nVoce pode seguir o correor pelo LESTE ou OESTE.", 0);
    salas[15] = criarSala("Voce anda pelo vasto corredor at� chegar em uma parte que possui espelhos em ambos as paredes.\nTal disposi��o de espelhos reflete a sua imagem infinitas vezes, o que te deixa desconfortavel.\nVoce pode seguir para o LESTE ou para OESTE.", 0);
    salas[16] = criarSala("Voce anda pelo vasto corredor ate encontrar uma porta grande de madeira.\nAo entrar na tal porta voce chega em um grande salao adornado com ouro e marmore e um tapete vermelho guiando ate uma escada adornada.\nVoce pode subir a escada pelo OESTE\nOu entrar em uma porta ao SUL.", 0);
    salas[17] = criarSala("Ao entrar pela porta, voce enxerga uma grande sala de jantar vazia.\nHa uma grande mesa com diversas cadeiras desarrumadas, pratos e talheres jogados, e comida sujando o ambiente, como se um jantar tivesse sido interrompido.\nVoce encontra um buraco na parede onde antes havia um quadro pelo OESTE\nOu voce pode voltar ao salao pelo NORTE.", 0);
    salas[18] = criarSala("Ao adentrar no quarto iluminado, voce imediatamente avista uma silhueta humana manchada de sangue na parede, como um inseto esmagado.\nEm cima de uma cama esta uma CHAVE em formato de um Serafim a qual voce imediatamente pega. Do lado ha um bilhete ilumidado por uma vela com fogo azul que podia se ler:\n'Nao escute seus susurros! Quando nos perdemos a tal ponto? Por que somente eu consigo ver? Por que somente eu consigo ver? Por que-' O bilhete foi interrompido...\nVoce pode somente voltar ao Mosteiro pelo LESTE.", 1);
    salas[19] = criarSala("", 0);
    salas[20] = criarSala("Voce se encontra em um corredor secreto dentro das paredes, parece que alguem espionava as pessoas por aqui.\nVoce pode entrar em uma passagem pelo SUL, mas parece ser dificil retornar...\nVoce pode tambem voltar para a sala de jantar pelo LESTE.\nOu voce pode sair por outro quadro mais a frente pelo NORTE.", 0);
    salas[21] = criarSala("Voce chega ao topo da escadaria. Pode se ver um grande quadro de um homem bem arrumado com os olhos negros como a noite.\nVoce consegue ver uma entrada por dentro do quadro levando ate o SUL\nOu voce pode seguir ate um corredor enxarcado com um liquido negro pelo NORTE.", 0);
    salas[22] = criarSala("", 0);
    salas[23] = criarSala("", 0);
    salas[24] = criarSala("Voce anda pelo corredor com um liquido negro. O cheiro de podrid�o permeia o ar.\nVoce consegue ir ate uma sala com um simbolo estranho na porta pelo LESTE.\nOu ir ate o topo das escadarias pelo SUL.", 0);
    salas[25] = criarSala("Voce se encontra no que parece ser uma sala totalmente destruida, as paredes sao compostas por teias de aranha e o mesmo liquido negro visto no corredor levando as escadarias. \nVoce consegue acessar um tunel liso e escorregadio que leva aos andares inferiores ao SUL\nOu seguir por um tunel que parece ter sido feito por algum tipo de animal pelo NORTE.", 0);
    salas[26] = criarSala("", 0);
    salas[27] = criarSala("", 1);
    salas[28] = criarSala("", 0);
    salas[29] = criarSala("Voce anda pelos tuneis da criatura.\nAo chegar no final, voce se ve em uma caverna ampla com agua escorrendo pelas paredes e formando um grande lago no centro.\n Voce pode seguir por um grande Portal com simbolos escritos com uma substancia negra pelo NORTE\n Ou seguir pelos tuneis da criatura pelo SUL.", 0);
    salas[30] = criarSala("", 0);
    salas[31] = criarSala("Voce agora se encontra em um corredor escuro, iluminado somente por uma luz vermelha vindo da fresta das paredes.\nAlgo naquele corredor nao parecia deste mundo, era como adentrar o submundo.\nVoce pode seguir o corredor pelo OESTE\nVoce pode entrar por um buraco estreito pelo LESTE, mas o caminho de volta parece ser dificil de fazer.\nOu voltar para caverna pelo SUL.", 0);
    salas[32] = criarSala("Voce esta em uma sala redonda. \nO chao possui um vidro que projeta uma luz carmesim no teto, revelando uma imagem de pessoas sofrendo em um purgatorio eterno comandandado por uma criatura de varias pernas.\nVoce sente que o seu destino pode ser decidido com a proxima escolha:\nVoce pode seguir pelo NORTE, adentrando uma enorme porta adornada com a mesma criatura vista diversas vezes.\nOu entrar em uma fresta preenchida com um liquido negro na parede pelo SUL, a qual parece nao ter mais volta.", 0);
    salas[33] = criarSala("Voce entra no que parece ser uma toca de aranha gigante. Um calafrio te domina, e voce fica enojado com o ambiente: \nO cheiro podre, por conta da quantidade enorme de cadaveres, permeia a sala, o que torna dificil de respirar.\nVoce ve diversos casulos pendurados em toda a sala envoltos pela mesma gosma negra vista anteriormente. Os casulos parecem se mecher.\nAo fundo voce enxerga uma porta com 5 ENTRADAS PARA CHAVES, cujo o acesso parece ter sido propositalmente protegido com a quantidade enorme de teias.", 0);
    salas[34] = criarSala("", 0);
    salas[35] = criarSala("", 0);
    salas[36] = criarSala("", 1);
    salas[37] = criarSala("", 0);
    salas[38] = criarSala("", 0);
    salas[39] = criarSala("", 0);
    salas[40] = criarSala("", 0);
    salas[41] = criarSala("", 0);
    salas[42] = criarSala("", 1);
    salas[43] = criarSala("", 0);
    salas[44] = criarSala("", 0);
    salas[45] = criarSala("Ao entrar na galeria, o ar frio e estagnado te envolve, um sussurro de misterios antigos.\nAs pinturas que adornam as paredes sao homenagens macabras � entidade que uma vez governou este lugar. \nCada tela eh um portal para uma vis�o perturbadora, onde anjos caidos veneram a criatura disfarcada, suas asas quebradas formando um coro sombrio ao redor do falso sacerdote.\nNo centro da sala consegue se ver uma chave em formato de um anjo Principado, a qual voce coleta.", 1);
    salas[46] = criarSala("", 0);
    salas[47] = criarSala("", 0);
    salas[48] = criarSala("", 0);
    salas[49] = criarSala("", 0);
    salas[50] = criarSala("", 0);
    
    //Conex�es entre as salas
    conectarSalas(salas[0], salas[1], 'N');
    conectarSalas(salas[1], salas[0], 'S');
    conectarSalas(salas[1], salas[2], 'L');
    conectarSalas(salas[1], salas[3], 'O');
    conectarSalas(salas[1], salas[4], 'N');
    conectarSalas(salas[2], salas[1], 'O');
    conectarSalas(salas[2], salas[5], 'L');
    conectarSalas(salas[5], salas[6], 'S');
    conectarSalas(salas[6], salas[5], 'N');
    conectarSalas(salas[6], salas[7], 'O');
    conectarSalas(salas[6], salas[7], 'O');
    conectarSalas(salas[7], salas[6], 'L');
    conectarSalas(salas[7], salas[0], 'O');
    conectarSalas(salas[3], salas[8], 'N');
    conectarSalas(salas[3], salas[1], 'L');
    conectarSalas(salas[8], salas[3], 'S');
    conectarSalas(salas[8], salas[4], 'L');
    conectarSalas(salas[4], salas[1], 'S');
    conectarSalas(salas[4], salas[8], 'O');
    conectarSalas(salas[4], salas[10], 'N');
    conectarSalas(salas[10], salas[4], 'S');
    conectarSalas(salas[8], salas[9], 'O');
    conectarSalas(salas[9], salas[12], 'O');
    conectarSalas(salas[12], salas[9], 'L');
    conectarSalas(salas[12], salas[13], 'S');
    conectarSalas(salas[13], salas[12], 'N');
    conectarSalas(salas[13], salas[18], 'O');
    conectarSalas(salas[18], salas[13], 'L');
    conectarSalas(salas[9], salas[11], 'N');
    conectarSalas(salas[9], salas[8], 'L');
    conectarSalas(salas[11], salas[9], 'S');
    conectarSalas(salas[11], salas[14], 'N');
    conectarSalas(salas[14], salas[11], 'S');
    conectarSalas(salas[14], salas[15], 'L');
    conectarSalas(salas[14], salas[16], 'O');
    conectarSalas(salas[16], salas[14], 'L');
    conectarSalas(salas[16], salas[17], 'S');
    conectarSalas(salas[16], salas[21], 'O');
    conectarSalas(salas[17], salas[16], 'N');
    conectarSalas(salas[17], salas[20], 'O');
    conectarSalas(salas[20], salas[17], 'L');
    conectarSalas(salas[20], salas[18], 'S');
    conectarSalas(salas[20], salas[21], 'N');
    conectarSalas(salas[21], salas[20], 'S');
    conectarSalas(salas[21], salas[45], 'O');
    conectarSalas(salas[21], salas[24], 'N');
    conectarSalas(salas[45], salas[21], 'L');
    conectarSalas(salas[24], salas[21], 'S');
    conectarSalas(salas[24], salas[25], 'L');
    conectarSalas(salas[25], salas[24], 'O');
    conectarSalas(salas[25], salas[16], 'S');
    conectarSalas(salas[25], salas[29], 'N');
    conectarSalas(salas[29], salas[25], 'S');
    conectarSalas(salas[29], salas[31], 'N');
    conectarSalas(salas[31], salas[29], 'S');
    conectarSalas(salas[31], salas[34], 'L');
    conectarSalas(salas[31], salas[32], 'O');
    conectarSalas(salas[32], salas[31], 'L');
    conectarSalas(salas[32], salas[24], 'S');
    conectarSalas(salas[32], salas[33], 'N');
    conectarSalas(salas[15], salas[14], 'O');
    conectarSalas(salas[15], salas[19], 'L');
    conectarSalas(salas[19], salas[15], 'O');
    conectarSalas(salas[19], salas[10], 'S');
    conectarSalas(salas[19], salas[22], 'L');
    conectarSalas(salas[22], salas[19], 'O');
    conectarSalas(salas[22], salas[23], 'N');
    conectarSalas(salas[23], salas[22], 'S');
    conectarSalas(salas[23], salas[27], 'L');
    conectarSalas(salas[27], salas[23], 'O');
    conectarSalas(salas[23], salas[26], 'O');
    conectarSalas(salas[23], salas[28], 'N');
    conectarSalas(salas[26], salas[23], 'L');
    conectarSalas(salas[26], salas[30], 'N');
    conectarSalas(salas[28], salas[23], 'S');
    conectarSalas(salas[28], salas[30], 'O');
    conectarSalas(salas[30], salas[26], 'S');
    conectarSalas(salas[30], salas[28], 'L');
    conectarSalas(salas[30], salas[34], 'N');
    conectarSalas(salas[34], salas[30], 'S');
    conectarSalas(salas[34], salas[35], 'N');
    conectarSalas(salas[35], salas[36], 'L');
    conectarSalas(salas[36], salas[35], 'O');
    conectarSalas(salas[35], salas[34], 'S');
    conectarSalas(salas[35], salas[37], 'O');
    conectarSalas(salas[35], salas[39], 'N');
    conectarSalas(salas[37], salas[35], 'L');
    conectarSalas(salas[37], salas[38], 'N');
    conectarSalas(salas[38], salas[37], 'S');
    conectarSalas(salas[38], salas[40], 'N');
    conectarSalas(salas[40], salas[38], 'S');
    conectarSalas(salas[38], salas[39], 'L');
    conectarSalas(salas[39], salas[35], 'S');
    conectarSalas(salas[39], salas[38], 'O');
    conectarSalas(salas[39], salas[46], 'N');
    conectarSalas(salas[46], salas[39], 'S');
    conectarSalas(salas[46], salas[49], 'N');
    conectarSalas(salas[46], salas[47], 'L');
    conectarSalas(salas[47], salas[46], 'O');
    conectarSalas(salas[47], salas[48], 'L');
    conectarSalas(salas[48], salas[47], 'O');
    conectarSalas(salas[48], salas[34], 'S');
    conectarSalas(salas[49], salas[46], 'S');
    conectarSalas(salas[49], salas[50], 'O');
    conectarSalas(salas[50], salas[49], 'L');
    conectarSalas(salas[50], salas[40], 'S');
    conectarSalas(salas[40], salas[50], 'N');
    conectarSalas(salas[40], salas[38], 'S');
    conectarSalas(salas[40], salas[41], 'O');
    conectarSalas(salas[41], salas[40], 'L');
    conectarSalas(salas[41], salas[42], 'O');
    conectarSalas(salas[42], salas[41], 'L');
    conectarSalas(salas[41], salas[43], 'S');
    conectarSalas(salas[43], salas[41], 'N');
    conectarSalas(salas[43], salas[44], 'S');
    conectarSalas(salas[44], salas[43], 'N');
    conectarSalas(salas[44], salas[34], 'S');
    conectarSalas(salas[44], salas[33], 'O');
    
    // Sala inicial
    Sala *salaAtual = salas[0];
    char comando[10];
    int chaves[6] = {0};

    // Loop principal do jogo
    while (1) {
        system("cls");
        exibirDescricao(salaAtual);
        if (salaAtual == salas[33]) 
		{
            if (verificarChavesColetadas(chaves, 6) == 1) 
			{
                printf("Voce conquistou o final 'Enviado de Deus'!\nObrigado por Jogar!");
            } else {
                printf("Voce sente uma presenca atras de voce, a imponencia de tal te faz ficar paralisado.\nA sua ultima memoria � ser abracado por diversas maos humanas e pilhas de dentes se fechando em seu pescoco.\nVoce conquistou o final 'Lamentacao'.\Tente achar todas as chaves e conquistar o final verdadeiro!");
            }
            break;
        }
              if (salaAtual == salas[10]) 
		{
            chaves[0] = 1;
            printf("Voce coletou a chave Querubim.\n");
        } 
		if (salaAtual == salas[18]) 
		{
            chaves[1] = 1;
            printf("Voce coletou a chave Serafim.\n");
        }
		if (salaAtual == salas[27]) 
		{ 
            chaves[2] = 1;
            printf("Voce coletou a chave Anjo.\n");
        }
		if (salaAtual == salas[36]) 
		{
            chaves[3] = 1;
            printf("Voce coletou a chave Trono.\n");
        }
		if (salaAtual == salas[42]) 
		{ 
            chaves[4] = 1;
            printf("Voce coletou a chave Principado!\n");
        }
		if (salaAtual == salas[45]) 
		{ 
            chaves[5] = 1;
            printf("Voce coletou a chave Arcanjo!\n");
        }
        salaAtual->chave = 0; 
        printf("Digite a direcao (N, S, L, O) ou 'sair' para encerrar: ");
        scanf("%s", comando);

        if (strcmp(comando, "sair") == 0) {
            printf("Saindo do jogo...\n");
            break;
        }

        int movimentoValido = 1;

        if (strcmp(comando, "N") == 0) {
            if (salaAtual->norte != NULL) {
                salaAtual = salaAtual->norte;
            } 
			else 
			{
                movimentoValido = 0;
            }
        } 
		else if (strcmp(comando, "S") == 0) 
		{
            if (salaAtual->sul != NULL) 
			{
                salaAtual = salaAtual->sul;
            } 
			else 
			{
                movimentoValido = 0;
            }
        } 
		else if (strcmp(comando, "L") == 0) 
		{
            if (salaAtual->leste != NULL) 
			{
                salaAtual = salaAtual->leste;
            } 
			else 
			{
                movimentoValido = 0;
            }
        } 
		else if (strcmp(comando, "O") == 0) 
		{
            if (salaAtual->oeste != NULL) 
			{
                salaAtual = salaAtual->oeste;
            } 
			else 
			{
                movimentoValido = 0;
            }
        } 
		else 
		{
            printf("Comando inv�lido. Tente novamente.\n");
            movimentoValido = 0;
        }

        if (!movimentoValido) 
		{
            printf("Movimento inv�lido\n");
            getch(); 
        }
    }

    for (int i = 0; i < 51; i++) {
        free(salas[i]);
    }

    return 0;
}


