const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

renderer.setClearColor(0xb7c3f3,1);//background color,opacity

const light = new THREE.AmbientLight( 0xffffff ); // soft white light
scene.add( light );

console.log("Good work");

camera.position.z = 5;

const loader = new THREE.GLTFLoader();



class Doll {
    constructor(){
        // Load a glTF resource
loader.load("./model/scene.gltf",
// called when the resource is loaded, callback function
function ( gltf ) {

    scene.add( gltf.scene );
    gltf.scene.scale.set(.4,.4,.4);
    gltf.scene.position.set(0,-1,0);
}
);
    }
}


let doll = new Doll;
function animate () {
    requestAnimationFrame(animate);    
    renderer.render(scene, camera);
};

animate();

window.addEventListener('resize',onWindowResize,false);

function onWindowResize(){
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    renderer.setSize(window.innerWidth,window.innerHeight);
}