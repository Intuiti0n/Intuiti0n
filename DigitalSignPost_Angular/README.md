# Digital Sign Post - Angular app

## About the App

This app had the following idea behind its creation: One user, multiple locations, location based narrative.
After a bit of research was conducted, a dynamic narrative was chosen, where the user would be the narrator of the story, since he decides which places he is going to visit, deciding where the story would start and where the next chapters would take place.

Each digital sign post has an associated ID and a matching location, and each location has a different story.


## Difficulties encountered / What did we learn

When I was starting this project, the lack of knowledge about web apps was the main obstacle in development. It required me to learn a bit about HTML, CSS, JS and how to user Angular.
HTML was used for the basic content of the website
CSS was used for the style of the website
angular provided the dynamic parts and interactivity, allowing us to build a single page application, with multiple components.
Cookies were used to store info about the user. Right now, I would probably use local storage for this purpose.

## Future work

Fix UI problems and improve the user experience
Fix some bugs
Alter the flow of the narrative, make it less static/boring

## More About the app

The app is based around the idea of have a user visiting several different real world locations, where "Digital Sign Posts" are placed. According to the place he visits, the narrative will evolve accordingly. By entering the app portal when connecting to the digital sign post, the user can choose our app, that gets the post ID in order to unlock the next chapter of the story.

If this is the first time that the user is playing the game, he will be asked to insert a username, saving the game info using cookies. After completing each story chapter the user can only unlock a new chapter by visiting another location in which a digital sign post is present.

## Application functionalities

- Present different content each time a user connects with the digital sign post
- Detect user location
- Re-route the user to different posts, without having a predefined route.
- Unlock new content when the user connects to the posts Wi-Fi network
- For each user, save the location logs and app actions

This app should be like a narrative game, with a fictional narrative or a history inspired in true events, historical events or not.  To make the users experience more challenging, the app should re-route the users to another post in an indirect way, giving them multiple narrative choices to choose from. Each choice will take the user to a different post, and the story should continue according with the users’ choice, adapting itself as the user progresses from one post to another.
This can prove to be an interesting concept for tourists, because they can engage in a story and know more about the city, visit different paths and monuments. When they arrive at a new post, the app should unlock that location, continue to the next chapter in the story, and give the user new choices to make.
So, this app should follow these steps:
•	User connects to the post, then it sends the log info to the server.
•	The app should update the story to show a new chapter, then let the user choose between multiple paths that the story can take. 
•	According to the users’ choice, the app indicates what post the user should visit next to continue the story.


Funcionalidades da aplicação

•	Apresentar conteúdo diferente sempre que um utilizador se conecta a um poste
•	Detetar localização do utilizador
•	Encaminhar o utilizador para diferentes postes e não ter apenas uma rota definida
•	Desbloquear conteúdos quando o utilizador se conecta à rede Wi-Fi de um poste
•	Criar um sistema de conquistas e recompensas para os utilizadores
•	Guardar um histórico de localizações e ações de cada utilizador num servidor

Para tornar a experiência desafiante para o utilizador, a aplicação deverá encaminhar os utilizadores para outro poste de forma indireta, isto é, sugerindo ao utilizador para se deslocar a um local fazendo referência a monumentos ou marcos importantes da área envolvente do poste, imagens, provérbios, etc. Esta abordagem é interessante, essencialmente, para turistas, porque se revela uma interessante “caça ao tesouro” para os utilizadores que desconhecem tais monumentos, podendo desta forma conhecer parte da historia e locais daquela zona/cidade. Quando o utilizador chega ao seu destino, a app deverá atribuir ao utilizador uma “conquista” (desbloquear aquela localização) e recompensa-lo ao fim de várias conquistas (1ª, 5ª, 10ª, etc) . Estas recompensas poderão ser, por exemplo, vouchers de descontos nos estabelecimentos vizinhos do poste onde o utilizador se conectou, ter acesso a mais conteúdo, ter opção de ver uma foto do monumento para o qual se deve deslocar, etc. 
Utilizador conecta-se ao poste
-> fazer log deste momento
->Ao iniciar a aplicação, apresentar varias alternativas de caminhos a seguir (rota aleatória)
-> o utilizador possui um perfil, com nível ou estatísticas de utilizador:
-Nº utilizador
-Nº de postes visitados
-Progresso/ nível
-Conquistas
->Caso escolha 1 alternativa, deve ser sugerida informação para que o utilizador chegue de forma indireta ao próximo poste, essa informação pode ser sugerida de variadas formas, pode ser uma foto de um local próximo, uma indicação de uma rua, um excerto de historia relacionado com esse local, um proverbio, algo que esteja relacionado com o local.
-> quando a pessoa for visitar o próximo local, deve repetir o processo, fazer log, desbloquear a conquista daquele sitio, debloquear novo conteúdo e talvez oferecer recompensa como por exemplo vouchers/descontos em lojas da zona. 
->Rating da app
A app deveria seguir o principio de uma narrativa, sendo apresentadas varias opções de narrativa, vários caminhos a seguir. De acordo com os postes para os quais se desloca, a história vai seguir um rumo diferente, adaptando-se de acordo com as “escolhas” do utilizador devido a ser este que escolhe para onde se deslocar.

FLUXO DA API
-> PESSOA LIGA-SE À API
-> INICIAR JOGO (criar novo user a cada inicio de sessao)
-> iNTRODUÇÃO - TUTORIAL
-> COMEÇA A HISTORIA DE ACORDO COM O POSTE ONDE SE ENCONTRA
	|-> COMO CRIAR POSTE VIRTUAL? QRCODE, CODIGO DE BARRAS, INSERIR CODIGO NO POSTE - > "CODIGO" IDENTIFICA A ZONA (BIOMA) 
	|->COMO APRESENTAR A HISTORIA :AMBIENTE GRAFICO, OU TEXTO  OU AMBOS
	|-> A NARRATIVA AVANÇ ATÉ UM CERTO PONTO MARCANTE (PARA PRENDER O UTILIZADOR AO JOGO)
		|->inserir novo "codigo" para continuar a historia/narrativa 
-> repetir os passos até ao fim da narrativa

Para avaliar da aplicação feita pelo grupo, será necessária uma avaliação externa, isto é,
um indivíduo externo ao grupo, que deverá seguir uma série de passos de forma a mais tarde
conseguir dar feedback ao grupo sobre quais os aspetos a melhorar ou se a aplicação se
enquadra ao que o mercado necessita.
Para isto, a equipa realizou um guião que esse utilizador, deverá seguir de forma a que
este siga também o fluxo da aplicação. Assim sendo, o utilizador deverá seguir os seguintes
passos:
1. Conectar-se à aplicação web;
2. Caso seja a primeira vez que se utiliza à aplicação, criará então um novo user.
Caso contrário, irá realizar login com as suas credenciais;
3. É apresentada uma nota introdutória sobre o funcionamento da aplicação e um
tutorial de forma a ensinar o utilizador como utilizar a aplicação recorrendo à
própria experiência de utilização. Este tutorial pode ser ignorado (skip) caso o
utilizador assim prefira;
4. A narrativa inicia-se sempre da mesma forma, sendo que o local onde o primeiro
capítulo decorre, depende da localização do poste;
5. A narrativa avança até um ponto marcante da história;
6. Após esse capítulo terminar o utilizador poderá deslocar-se para outro poste;
7. Repetir os pontos 4 a 6 até acabar a história;
De forma a ser possível realizar este guião o grupo teve de pensar em formas de simular
o “ambiente” em que a aplicação poderá ser utilizada, dado que para testar este conceito não é
possível utilizar por agora os postes já colocados em diferentes localizações. O grupo pensou
assim na utilização de QRcodes (numa fase posterior) e nesta fase inicial usar um código
(location tag) que é inserido pelo utilizador, sendo que cada “poste" terá o seu código específico
sendo assim possível identificar o bioma, zona, em que se encontra.

Ideias para a APP WEB:
Principio base:
1 user, varios locais.
levar o utilizador a visitar varios sitios de interesse.

Criar uma aplicação WEB, que quando o user se conecta a um post,
envia um request pro servidor em que este deteta que o user visitou aquele local,
apresenta as "missoes" daquele post, com dicas, frases, imagens ou referencias de locais pra visitar,
locais que sao referentes a diferentes categorias: historia, desporto, musica,
expressoes populares, restauraçao, etc.

