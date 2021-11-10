const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

renderer.setClearColor(0xb7c3f3, 1);//background color,opacity

const light = new THREE.AmbientLight(0xffffff); // soft white light
scene.add(light);

console.log("Good work");

function createCube(size,positionX) {
    const geometry = new THREE.BoxGeometry(size.w,size.h,size.d);
    const material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
    const cube = new THREE.Mesh(geometry, material);
    cube.position.x = positionX;
    scene.add(cube);
}

camera.position.z = 5;

const loader = new THREE.GLTFLoader();



class Doll {
    constructor() {
        // Load a glTF resource
        loader.load("./model/scene.gltf", (gltf) => {

            scene.add(gltf.scene);
            gltf.scene.scale.set(.4, .4, .4);
            gltf.scene.position.set(0, -1, 0);
            this.doll = gltf.scene;
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
    createCube({w:.2,h:.5,d:.5},4);
}

createTrack();

let doll = new Doll;

setTimeout(() => {
    doll.lookBackward();
    console.log("Look back");
}, 1000);


setTimeout(() => {
    doll.lookForward();
    console.log("Look forward");
}, 2000);


//doll.lookBack();
function animate() {
    requestAnimationFrame(animate);
    renderer.render(scene, camera);
};

animate();

window.addEventListener('resize', onWindowResize, false);

function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    renderer.setSize(window.innerWidth, window.innerHeight);
}