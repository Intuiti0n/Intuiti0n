# Digital Sign Post - Angular app

This readme is still in progress

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

- User connects to the post, then it sends the log info to the server.
- The app should update the story to show a new chapter, then let the user choose between multiple paths that the story can take.
- According to the users’ choice, the app indicates what post the user should visit next to continue the story.

## Organize the functionalities

- Present different content every time a user connects to a post
- Detect user location
- Redirect the user to different posts and don't have only a pre-defined route
- Unlock content when the user connects to the wifi post network
- Create a challenge and reward system for the users
- Save a location history and actions for each user on a server

To make this a compeling and challenging experience for the user, the app should redirect them to another post in an indirect way, suggesting the user to go to another location, by refering nearby monuments or relevant milestones, showing pictures, common sayings for the area, etc. This approach is interesting, specially for tourists, because it resembles a treasure hunt game, letting the unfamiliar users get to know new and cool spots, teaching them the history of those places. When the user arrives at a new locations, the app should unlock an achievement "Location Unlocked" and reward him after a few achievements (1º, 5º, 10º location unlocked, etc) This rewards could be, for instance, discount coupons for local shops of that area, access more content, get hints for more spots to visit, etc.

## Tasks

1. User connects to the post

- Log this moment
- When starting the app, show a number of routes to follow (random routes)
- The user has a profile, with level or statistics
	- User number
	- Number of locations visited
	- Progress / Level
	- Achievements
- If he chooses 1 alternative, information should be provided for the user to reach the next post (give some tips, lore, picture, something related to the place)
- When the person visits the next spot, the process should be repeated: log, unlock location, unlock new content, maybe offer reward
- App rating (Future Work)

2. API flow

- User connects to the API
- Start game (create new user when it is the first connection)
- Intro -> Tutorial
- Start the story according to the location
	- How to create a virtual post? QRCODE? CODEBAR? insert code on post? code identifies area/biome
	- How to present the story? graphic interface? text? both?
	- The narrative advances till a certain cliffhanger moment
- Insert new code to continue story
- Repeat till the end of the story

<!--
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
-->
