const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

renderer.setClearColor(0xb7c3f3, 1);//background color,opacity

const light = new THREE.AmbientLight(0xffffff); // soft white light
scene.add(light);

const directionalLight = new THREE.DirectionalLight( 0xffffff, 0.3 );
directionalLight.castShadow = true;
scene.add( directionalLight );
directionalLight.position.set( 0, 1, 1 );

console.log("Good work");

//create global variables
const start_position = -3;
const end_pos = -start_position;

const text = document.querySelector('.text');

let DEAD_PLAYERS = 0;
let SAFE_PLAYERS = 0;

const startBtn = document.querySelector('.start-btn')

//musics
const bgMusic = new Audio('./music/bg.mp3');
bgMusic.loop = true
const winMusic = new Audio('./music/win.mp3');
const loseMusic = new Audio('./music/lose.mp3');


function createCube(size, positionX, rotY = 0, color = 0xfbc851) {
    const geometry = new THREE.BoxGeometry(size.w, size.h, size.d);
    const material = new THREE.MeshBasicMaterial({ color: color });
    const cube = new THREE.Mesh(geometry, material);
    cube.position.x = positionX;
    cube.rotation.y = rotY;
    scene.add(cube);

    return cube;
}

camera.position.z = 5;

const loader = new THREE.GLTFLoader();



class Doll {
    constructor() {
        // Load a glTF resource
        loader.load("./model/scene.gltf", (gltf) => {

            gltf.scene.position.set(0,-1, 0);
            gltf.scene.scale.set(0.4, 0.4, 0.4);
            startBtn.innerText = "start";
        });
    }

    lookBackward() {
        //this.doll.rotation.y = Math.PI;
        gsap.to(this.doll.rotation, { y: -3.15, duration: .45 })
    }

    lookForward() {
        //this.doll.rotation.y = 0;
        gsap.to(this.doll.rotation, { y: 0, duration: .45 })
    }
}

function createTrack() {
    createCube({ w: .2, h: 1.5, d: 1 }, start_position, -.35);
    createCube({ w: .2, h: 1.5, d: 1 }, end_pos, .35);
    createCube({ w: start_position * 2.2, h: 1.5, d: 1 }, 0, 0, 0xe5a716).position.z = -1;
}

createTrack();

class Player {
    constructor(name = "Player", radius = .25, posY = 0, color = 0xffffff){
        const geometry = new THREE.SphereGeometry( radius, 100, 100 )
        const material = new THREE.MeshBasicMaterial( { color } )
        const player = new THREE.Mesh( geometry, material )
        scene.add( player )
        player.position.x = start_position - .4
        player.position.z = 1
        player.position.y = posY
        this.player = player
        this.playerInfo = {
            positionX: start_position - .4,
            velocity: 0,
            name,
            isDead: false
        }
    }

    run(){
        if(this.playerInfo.isDead) return
        this.playerInfo.velocity = .03
    }

    stop(){
        gsap.to(this.playerInfo, { duration: .1, velocity: 0 })
    }

    check(){
        if(this.playerInfo.isDead) return
        if(!dallFacingBack && this.playerInfo.velocity > 0){
            text.innerText = this.playerInfo.name + " lost!!!"
            this.playerInfo.isDead = true
            this.stop()
            DEAD_PLAYERS++
            loseMusic.play()
            if(DEAD_PLAYERS == players.length){
                text.innerText = "Everyone lost!!!"
                gameStat = "ended"
            }
            if(DEAD_PLAYERS + SAFE_PLAYERS == players.length){
                gameStat = "ended"
            }
        }
        if(this.playerInfo.positionX < end_position + .7){
            text.innerText = this.playerInfo.name + " is safe!!!"
            this.playerInfo.isDead = true
            this.stop()
            SAFE_PLAYERS++
            winMusic.play()
            if(SAFE_PLAYERS == players.length){
                text.innerText = "Everyone is safe!!!"
                gameStat = "ended"
            }
            if(DEAD_PLAYERS + SAFE_PLAYERS == players.length){
                gameStat = "ended"
            }
        }
    }

    update(){
        this.check()
        this.playerInfo.positionX -= this.playerInfo.velocity
        this.player.position.x = this.playerInfo.positionX
    }
}

async function delay(ms){
    return new Promise(resolve => setTimeout(resolve, ms))
}

const player1 = new Player("Player 1", .25, .3, 0xD1FFC6)
const player2 = new Player("Player 2", .25, -.3, 0xFFCFD2)

const players = [
    {
        player: player1,
        key: "ArrowUp",
        name: "Player 1"
    },
    {
        player: player2,
        key: "w",
        name: "Player 2"
    }
]

const TIME_LIMIT = 15
async function init(){
    await delay(500)
    text.innerText = "Starting in 3"
    await delay(500)
    text.innerText = "Starting in 2"
    await delay(500)
    text.innerText = "Starting in 1"
    lookBackward()
    await delay(500)
    text.innerText = "Gooo!!!"
    bgMusic.play()
    start()
}

let gameStat = "loading"

function start(){
    gameStat = "started"
    const progressBar = createCube({w: 8, h: .1, d: 1}, 0, 0, 0xebaa12)
    progressBar.position.y = 3.35
    gsap.to(progressBar.scale, {duration: TIME_LIMIT, x: 0, ease: "none"})
    setTimeout(() => {
        if(gameStat != "ended"){
            text.innerText = "Time Out!!!"
            loseMusic.play()
            gameStat = "ended"
        }
    }, TIME_LIMIT * 1000)
    startDall()
}

let dallFacingBack = true
async function startDall(){
   lookBackward()
   await delay((Math.random() * 1500) + 1500)
   lookForward()
   await delay((Math.random() * 750) + 750)
   startDall()
}


startBtn.addEventListener('click', () => {
    if(startBtn.innerText == "START"){
        init()
        document.querySelector('.modal').style.display = "none"
    }
})

function animate(){
    renderer.render( scene, camera )
    players.map(player => player.player.update())
    if(gameStat == "ended") return
    requestAnimationFrame( animate )
}
animate()

window.addEventListener( "keydown", function(e){
    if(gameStat != "started") return
    let p = players.find(player => player.key == e.key)
    if(p){
        p.player.run()
    }
})
window.addEventListener( "keyup", function(e){
    let p = players.find(player => player.key == e.key)
    if(p){
        p.player.stop()
    }
})

window.addEventListener( 'resize', onWindowResize, false )
function onWindowResize(){
    camera.aspect = window.innerWidth / window.innerHeight
    camera.updateProjectionMatrix()
    renderer.setSize( window.innerWidth, window.innerHeight )
}