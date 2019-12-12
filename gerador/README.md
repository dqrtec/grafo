# gerador
Gerador de grafos

Apartir do seculo 21 há um grande aumento na busca em banco de dados não relacionais por ofertarem mais flexibilidade na manipulação dos dados. Podendo sitar os banco de dados em grafos como o Neo4J que está em 22º no rank de banco de dados mais utilizados(https://db-engines.com/en/ranking).

A aplicação se destina a auxiliar a criar dados para um banco de dados orientado a grafos, de forma a ser possivel que outras pessoas possam criar massa de teste para verificar escalabilidade de outros sistemas mediantes um padrão único a ser encontrado. 

(Aplicação): É uma ferramenta de geração de benckmark para banco de dados orientados a grafos. Cujo principal diferencial é a garantia de conter um subgrafo especificado pelo usuário.

Na maioria das vezes há apenas uma exportação dos dados de uma base relacional para um banco de dados em grafos, demandado tempo e a necessidade de garantir que o banco relacional possua os dados com as caracteristicas que se desejam observar no grafo.

Diante desse problema, foi criado o (Aplicação) com o intuito de gerar rapidamente um grafo de tamanho mensurável que contenha padrões em que se deseja analisar.

Na Seção 2 iremos descrever o principal fluxo da aplicação, detalhando o codigo e usbilidade da aplicação. Na Seção 3 mostraremos a conclusão do projeto. Na Seção 4 iremos tratar de trabalhos futuros.

APLICAÇÃO

	***EXPLICAR DELTA

A (Aplicação) foi implementada com a intenção de, apartir de um grafo rotulado determinado pelo usuário, criar um grande grafo,G, de teste contendo tal grafo. Garantindo sempre uma quantidade específica de subgrafos, que fora fornecido pelo usuário. Para tanto, a plicação permite que o usuário utilize recursos gráficos da aplicação para a criação do grafo que denominaremos de 'Query'. Além disso deve permitir que o usário defina o tamanho do grafo G que deverá ser gerado, especificando o numero de vertices,|Vg|, e o numero de arestas,|Eg|. Após a execução do aplicativo, será salvo, em um arquivo de texto, o grafo com rotulos, com uma formatação propria.

Os grafos dessa aplicação possuem arestas não ponderadas e vertices com rótulos. Podendo ,contudo, ser desconexo.

A principal dificuldade dessa aplicação é construir um grafo grande rotulado e garantir a unicidade de padrões definido pelo usuário. Pois dessa forma o usuário poderá criar consultas sobre essa base de dados, e medir o tempo de resposta sobre essa consulta, por exemplo.

Os grafos gerados pela aplicação têm a seguinte estrutura. Primeira linha contem o numero de vertices,n = |Gn|, do grafo seguido do numero de arestas,m = |Gm|. As próximas n linhas contêm o identificador ,inteiro, de cada vertice seguido do seu rótulo. As m linhas seguintes contem o identificador de dois vertices, identicando a existencia de arestas entre esses vertices.

Para gerar um grafo mais parecido com dados reais, é possível o usuário inserir o grau mestre do grafo, um numero decimal. O Grafo que será gerado terá esse grau mestre.

(CODIGOS)
Query Expandida
	no código 1 estamos recebendo o grafo 'Query' fornecido pelo usuário. Iremos aumentá-lo para que todos os vertices fiquem a uma distancia de pelo menos δ entre os vertices, adicionando vertices e arestas entre dois vertices da 'Query',subdivisão de arestas. E garantir que exista apenas uma resposta apartir de um δ' >= δ 

	[colocar codigo aqui]

Linking Tree
	Apartir da Query expandida, adicionaremos a G vertices de modo a garantir a quantidade de vertices do grafo. Serão adicionadas arestas de modo a sempre criar uma árvore pois desta forma garantimos que não haverá ciclos e consequentiemente não haverá um caminho mais curto entre vertices 'Query'. Os vertices que são adicionados não terão os rotulos pertencentes ao grafo 'Query' para garantir que não haverá mais de um padrão dentro do grafo.

	[colocar codigo aqui]

Linking Graph
	Agora iremos garantir perder a estrutura de arvore para garantir a quantidade de arestas que o grafo conterá e tomando cuidado de não criar um caminho mais curto que a propria query entre seus vertices

	[colocar codigo aqui]

Análise de Geração de grafos Comparativa
	"quanto tempo demora para gerar os grafos"
	grafo : caminho , meio termo , completo
	n : 10 , 100 , 1000
	m : caminho , meio termo , completo

Considerações finais
	
