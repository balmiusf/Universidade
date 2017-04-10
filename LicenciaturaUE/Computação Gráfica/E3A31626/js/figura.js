TweenApp = function() {
    Sim.App.call(this);
    
}

TweenApp.prototype = new Sim.App();


TweenApp.prototype.init = function(param) {
    //
    Sim.App.prototype.init.call(this, param);
    //
    scene = new THREE.Scene(); // criar uma cena
    var light = new THREE.PointLight( 0xffffff, 1.5); // criar luz
    light.position.set(0, 0, 20);
    this.scene.add(light); // adicionar a cena
    
     camera = new THREE.PerspectiveCamera(45, container.offsetWidth / container.offsetHeight, 1, 4000 ); // criar uma camara
    camera.position.set( 0, 0, 100 );



    renderer = new THREE.WebGLRenderer( { antialias: true } );
    this.renderer.setClearColor( 0xffffff, 1);
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize( window.innerWidth, window.innerHeight ); // alterar o tamanho

    this.camera.position.set( 0, 0, 100 );    // alterar a camara

    var animar = new Animacao();
    animar.init();
    this.addObject(animar);
    
    this.animar = animar;
}

// realizar o resize
function reSize() 
{
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    renderer.setSize( window.innerWidth, window.innerHeight );

}

// funcao que crias as pernas da figura
function pernas(corpo_material,hoof_material)
{
    perna_esquerda = new THREE.Object3D(); // criar grupo

    // criar geometria 
    // a perna e composta por tres componentes excepto o hoof
    var perna_p1 = new THREE.BoxGeometry(5,7,5);
    var perna_p1_1 = new THREE.BoxGeometry(5,7,5);
    var perna_p2 = new THREE.BoxGeometry(4,12,3.1);

    // criar hoofs

    var hoof = new THREE.BoxGeometry(3,4,3);
    

    //criar mesh

    perna_p1_mesh = new THREE.Mesh(perna_p1,corpo_material); 
    perna_p1_1_mesh = new THREE.Mesh(perna_p1_1,corpo_material);
    perna_p2_mesh = new THREE.Mesh(perna_p2,corpo_material);

    hoof_mesh = new THREE.Mesh(hoof,hoof_material);


    // alterar posicoes e vertices
    // alteracao dos vertices pa gerar efeito que se ve na figura

    perna_p1_mesh.position.set(0.5,-5,6);
    perna_p1_mesh.rotation.z += 0.05;

    perna_p1_mesh.geometry.vertices[0].z -= 1.05; // alterar a expessura da perna
    perna_p1_mesh.geometry.vertices[4].z += 1.05;

    perna_p1_mesh.geometry.vertices[1].z += 1.05;
    perna_p1_mesh.geometry.vertices[5].z -= 1.05;
    

    perna_p2_mesh.position.set(0.5,-17,6);
    perna_p2_mesh.geometry.vertices[2].x -= 1.0;
    perna_p2_mesh.geometry.vertices[3].x -= 1.0;

    perna_p2_mesh.geometry.vertices[0].z += 1.05; // alterar a expessura da perna
    perna_p2_mesh.geometry.vertices[4].z -= 1.05;

    perna_p2_mesh.geometry.vertices[1].z -= 1.05;
    perna_p2_mesh.geometry.vertices[5].z += 1.05;


    perna_p1_1_mesh.position.set(0.5,-11,6);
    perna_p1_1_mesh.geometry.vertices[2].x -=1;
    perna_p1_1_mesh.geometry.vertices[3].x -= 1;
    perna_p1_1_mesh.geometry.vertices[6].x += 0.5;
    perna_p1_1_mesh.geometry.vertices[7].x += 0.5;



    // hoof //

    hoof_mesh.position.set(0.2,-24,6);
    hoof_mesh.geometry.vertices[6].x -= 1;
    hoof_mesh.geometry.vertices[7].x -= 1;

    // adicionar ao grupo

    perna_esquerda.add(perna_p1_1_mesh);
    perna_esquerda.add(perna_p2_mesh);
    perna_esquerda.add(perna_p1_mesh);
    perna_esquerda.add(hoof_mesh);

    perna_esquerda.position.set(2,0,0); 

    var perna_direita = perna_esquerda.clone(); // criar clone da outra perna
    perna_direita.position.set(2,0,-12);

    var pernas = new THREE.Object3D(); // criar grupo de pernas 

    pernas.add(perna_esquerda); // adicionar as pernas 
    pernas.add(perna_direita);

    return pernas; // devolver grupo 
}

// funcao que recebo as texturas necessarias e retorna um grupo que contem todos os mesh que fazem parte da cauda
function cauda(cauda_material, cauda_vermelha_material)
{
    var cauda = new THREE.Object3D(); // criar grupo

    // criar geometria a cauda e composto por 5 partes iguais (com modificacoes em vertices para se conseguir encaixar na perfeicao)
    //  a excepcao da ultima parte (cauda_p6) que sera mais tarde transformada atraves
    // de modificacao de vertices numa piramide quadrangular 
    var cauda_p1 = new THREE.BoxGeometry(15, 13, 13);
    var cauda_p2 = new THREE.BoxGeometry(15, 11, 11);
    var cauda_p3 = new THREE.BoxGeometry(15, 9, 9);
    var cauda_p4 = new THREE.BoxGeometry(15, 7, 7);
    var cauda_p5 = new THREE.BoxGeometry(15, 5, 5);
    var cauda_p6 = new THREE.BoxGeometry(15,3,3);


    // criar mesh 
    cauda_p4_mesh = new THREE.Mesh(cauda_p4,cauda_material);
    cauda_p5_mesh = new THREE.Mesh(cauda_p3,cauda_material);
    cauda_p2_mesh = new THREE.Mesh(cauda_p2,cauda_material);
    cauda_p1_mesh = new THREE.Mesh(cauda_p1,cauda_material);
    ponta_cauda_mesh = new THREE.Mesh(cauda_p5, cauda_vermelha_material);
    ponta_cauda_2_mesh = new THREE.Mesh(cauda_p6, cauda_vermelha_material);

    // alterar posicoes e vertices de cada geometria para provocar o efeito que se pode ver na figura 

    ponta_cauda_2_mesh.position.set(105,0,0);

    ponta_cauda_2_mesh.geometry.vertices[4].z -= 1.0;
    ponta_cauda_2_mesh.geometry.vertices[5].z += 1;
    ponta_cauda_2_mesh.geometry.vertices[4].y += 1;
    ponta_cauda_2_mesh.geometry.vertices[5].y += 1;

    ponta_cauda_2_mesh.geometry.vertices[6].y += -1;
    ponta_cauda_2_mesh.geometry.vertices[7].y += -1;
    ponta_cauda_2_mesh.geometry.vertices[6].z -= 1;
    ponta_cauda_2_mesh.geometry.vertices[7].z += 1;

    // criar piramida rectangular

    ponta_cauda_2_mesh.geometry.vertices[0].y -= 1.5;
    ponta_cauda_2_mesh.geometry.vertices[1].y -= 1.5;
    ponta_cauda_2_mesh.geometry.vertices[2].y += 1.5;
    ponta_cauda_2_mesh.geometry.vertices[3].y += 1.5;

    //

    ponta_cauda_mesh.position.set(90,0,0);

    ponta_cauda_mesh.geometry.vertices[4].z -= 1.0;
    ponta_cauda_mesh.geometry.vertices[5].z += 1;
    ponta_cauda_mesh.geometry.vertices[4].y += 1;
    ponta_cauda_mesh.geometry.vertices[5].y += 1;

    ponta_cauda_mesh.geometry.vertices[6].y += -1;
    ponta_cauda_mesh.geometry.vertices[7].y += -1;
    ponta_cauda_mesh.geometry.vertices[6].z -= 1;
    ponta_cauda_mesh.geometry.vertices[7].z += 1;


    cauda_p4_mesh.position.set(75,0,0);

    cauda_p4_mesh.geometry.vertices[4].z -= 1.0;
    cauda_p4_mesh.geometry.vertices[5].z += 1;
    cauda_p4_mesh.geometry.vertices[4].y += 1;
    cauda_p4_mesh.geometry.vertices[5].y += 1;

    cauda_p4_mesh.geometry.vertices[6].y += -1;
    cauda_p4_mesh.geometry.vertices[7].y += -1;
    cauda_p4_mesh.geometry.vertices[6].z -= 1;
    cauda_p4_mesh.geometry.vertices[7].z += 1;


    cauda_p5_mesh.position.set(60,0,0);

    cauda_p5_mesh.geometry.vertices[4].z -= 1.0;
    cauda_p5_mesh.geometry.vertices[5].z += 1;
    cauda_p5_mesh.geometry.vertices[4].y += 1;
    cauda_p5_mesh.geometry.vertices[5].y += 1;

    cauda_p5_mesh.geometry.vertices[6].y += -1;
    cauda_p5_mesh.geometry.vertices[7].y += -1;
    cauda_p5_mesh.geometry.vertices[6].z -= 1;
    cauda_p5_mesh.geometry.vertices[7].z += 1;


    cauda_p2_mesh.position.set(45,0,0);
    cauda_p2_mesh.geometry.vertices[4].z -= 1.0;
    cauda_p2_mesh.geometry.vertices[5].z += 1;
    cauda_p2_mesh.geometry.vertices[4].y += 1;
    cauda_p2_mesh.geometry.vertices[5].y += 1;

    cauda_p2_mesh.geometry.vertices[6].y += -1;
    cauda_p2_mesh.geometry.vertices[7].y += -1;
    cauda_p2_mesh.geometry.vertices[6].z -= 1;
    cauda_p2_mesh.geometry.vertices[7].z += 1;

    cauda_p1_mesh.position.set(30,0,0);
    cauda_p1_mesh.geometry.vertices[4].z -= 1;
    cauda_p1_mesh.geometry.vertices[5].z += 1;
    cauda_p1_mesh.geometry.vertices[4].y += 1;
    cauda_p1_mesh.geometry.vertices[5].y += 1;

    cauda_p1_mesh.geometry.vertices[6].y += -1;
    cauda_p1_mesh.geometry.vertices[7].y += -1;
    cauda_p1_mesh.geometry.vertices[6].z -= 1;
    cauda_p1_mesh.geometry.vertices[7].z += 1;

    // adicionar os mesh ao grupo 
    cauda.add(cauda_p1_mesh);
    cauda.add(cauda_p2_mesh);
    cauda.add(cauda_p5_mesh);
    cauda.add(cauda_p4_mesh);
    cauda.add(ponta_cauda_mesh);
    cauda.add(ponta_cauda_2_mesh);

    return cauda; // devolver grupo
}

// funcao que recebe a textura necessaria, cria e retorna um grupo com todos os elementos que fazem parte do corpo
function corpo(corpo_material)
{
 
    var corpo = new THREE.Object3D(); // criar grupo

    // criar figuras
    var corpo_p1 = new THREE.BoxGeometry(25, 15, 15);
    var corpo_p2 = new THREE.BoxGeometry(13,7,7);   
    var belly = new THREE.BoxGeometry(25,10,15);

    // criar mesh

    belly_mesh = new THREE.Mesh(belly, corpo_material);
    corpo_p1_mesh = new THREE.Mesh(corpo_p1, corpo_material);
    corpo_p2_mesh = new THREE.Mesh(corpo_p2,corpo_material);
    var mesh_corpo = new THREE.Mesh(corpo_p2,corpo_material);

    // alteracao nas posicoes e nos pontos 
    corpo_p1_mesh.position.set(10,0,0); // corpo
    corpo_p1_mesh.geometry.vertices[4].z += 3;
    corpo_p1_mesh.geometry.vertices[5].z -= 3;

    belly_mesh.position.set(10,-12.5,0);
    belly_mesh.geometry.vertices[2].x -= 12;
    belly_mesh.geometry.vertices[3].x -= 12;

    belly_mesh.geometry.vertices[3].z += 3;
    belly_mesh.geometry.vertices[2].z -= 3;

    belly_mesh.geometry.vertices[6].x += 2;
    belly_mesh.geometry.vertices[7].x += 2;
    belly_mesh.geometry.vertices[6].y += 2;
    belly_mesh.geometry.vertices[7].y += 2;
    belly_mesh.geometry.vertices[6].z += 3;
    belly_mesh.geometry.vertices[7].z -= 3;

    // alteracoes na posicao e rotacoes

    corpo_p2_mesh.position.set(6,5,0);
    corpo_p2_mesh.rotation.z += -0.10 ;

    mesh_corpo.position.set(5,5,0);
    mesh_corpo.rotation.z += -0.15 ;

    // adicionar ao grupo 
    corpo.add(corpo_p2_mesh);
    corpo.add(mesh_corpo);
    corpo.add(belly_mesh);
    corpo.add(corpo_p1_mesh);

    return corpo; // devolver grupo 
}

// funcao que recebe a textura necessaria, cria e retorna um grupo com todos os elementos que fazem parte do corpo
function cornos(corno_material)
{
	cornos = new THREE.Object3D();
	
    // criar geometria 
    var corno = new THREE.CylinderGeometry(0, 1.5, 6, 8, 1, false);
 	
    // criar mesh
 	corno_mesh = new THREE.Mesh(corno,corno_material);
    corno_mesh_dir = new THREE.Mesh(corno,corno_material); // aproveitar geometria ja criada e criar um segundo corno identico


    // alterar posicoes, rotacoes 
    corno_mesh_dir.position.set(-4,10.5,-4);
    corno_mesh_dir.rotation.x = -0.45;
    corno_mesh_dir.rotation.z = 0.45;
    
    corno_mesh.position.set(-4,10.5,4);
    corno_mesh.rotation.x = 0.45;
    corno_mesh.rotation.z = 0.45;

    // adicionar ao grupo 
    cornos.add(corno_mesh); 
    cornos.add(corno_mesh_dir);

    return cornos;
}

// funcao que recebe a textura necessaria, cria e retorna um grupo com todos os elementos que fazem parte do corpo

function cabeca(corpo_material, cara_materials)
{

    cabeca = new THREE.Object3D(); // criar grupo


    // criar geometria 
    var orelhas = new THREE.BoxGeometry(3,3,0);
    var maxilar = new THREE.BoxGeometry(10,1,8);
    var pescoco = new THREE.BoxGeometry(10,7,9);
    var focinho = new THREE.BoxGeometry(13.5,5,8);
    var olhos = new THREE.BoxGeometry(5,4,7);
    var detalhe_cara = new THREE.BoxGeometry(3,2,7);


    // criar mesh
    orelhas_mesh = new THREE.Mesh(orelhas,corpo_material);
    orelhas_mesh_esq = new THREE.Mesh(orelhas,corpo_material);
    maxilar_mesh = new THREE.Mesh(maxilar,corpo_material);
    olhos_mesh = new THREE.Mesh(olhos,new THREE.MeshFaceMaterial(cara_materials));
    focinho_mesh = new THREE.Mesh(focinho,corpo_material);
    pescoco_mesh = new THREE.Mesh(pescoco,corpo_material);
    detail_face = new THREE.Mesh(detalhe_cara, corpo_material);


    // alterar posicoes e rotacoes 
    orelhas_mesh_esq.position.set(-3,8,5.1);
    orelhas_mesh_esq.rotation.z = 2.6;
    orelhas_mesh_esq.rotation.y = 0;
    orelhas_mesh_esq.rotation.x = 2.6;

    orelhas_mesh.position.set(-3,8,-5);
    orelhas_mesh.rotation.z = 0.45;
    orelhas_mesh.rotation.y = 0;
    orelhas_mesh.rotation.x = 0.45;

    maxilar_mesh.position.set(-6.5,3,0);
    maxilar_mesh.rotation.z = 0.45;

    detail_face.position.set(-9.3,6.3,0);
    detail_face.rotation.z += 1.1;
  
    focinho_mesh.position.set(-5,4.5,0);
    focinho_mesh.rotation.z +=0.3;
    
    pescoco_mesh.position.set(-1,4.4,0);
    pescoco_mesh.rotation.z += -0.5;
    
    olhos_mesh.rotation.z = 0.3;
    olhos_mesh.position.set(-6.4,7,0);



    // adicionar ao grupo 
    cabeca.add(orelhas_mesh);
    cabeca.add(orelhas_mesh_esq)
    cabeca.add(maxilar_mesh);
    cabeca.add(olhos_mesh);
    cabeca.add(focinho_mesh);
    cabeca.add(pescoco_mesh);
    cabeca.add(detail_face);

    return cabeca; // retornar grupo
}

// actualizar os tweens
TweenApp.prototype.update = function() {

    TWEEN.update();
    //
    Sim.App.prototype.update.call(this);
}
// classe animacao
Animacao = function() {
    Sim.Object.call(this);
}

Animacao.prototype = new Sim.Object();
//
Animacao.prototype.init = function() {
    
    //  todas as texturas necessarias para a figura 
        var mapUrlCauda = "texturas/Cauda.jpg";
        var map_cauda = THREE.ImageUtils.loadTexture(mapUrlCauda);

    var mapUrlCorpo = "texturas/corpo.jpg";
    var map_corpo = THREE.ImageUtils.loadTexture(mapUrlCorpo);

    var mapUrlCorno = "texturas/corno.jpg";
    var map_corno = THREE.ImageUtils.loadTexture(mapUrlCorno);

    var mapUrlCauda_V = "texturas/cauda_vermelha.jpg";
    var map_cauda_v = THREE.ImageUtils.loadTexture(mapUrlCauda_V);

   	var mapHoofUrl = "texturas/hoof.jpg";  
	 var mapHoof = THREE.ImageUtils.loadTexture(mapHoofUrl);


	// array com varias texturas diferentes em cada face ( especifico para a cara da figura)

    var cara_materials = [
    new THREE.MeshLambertMaterial({
        ambient: 0xffffff,
        map: THREE.ImageUtils.loadTexture( 'texturas/cara0.jpg' ) }),
    new THREE.MeshLambertMaterial({
        ambient: 0xffffff,
        map: THREE.ImageUtils.loadTexture( 'texturas/cara0.jpg' ) }),
    new THREE.MeshLambertMaterial({
        ambient: 0xffffff,
        map: THREE.ImageUtils.loadTexture( 'texturas/cara0.jpg' ) }),
    new THREE.MeshLambertMaterial({
        ambient: 0xffffff,
        map: THREE.ImageUtils.loadTexture( 'texturas/cara0.jpg' ) }),
    new THREE.MeshLambertMaterial({
        ambient: 0xffffff,
        map: THREE.ImageUtils.loadTexture( 'texturas/cara4.jpg' ) }),
    new THREE.MeshLambertMaterial( {
        ambient: 0xffffff,
        map: THREE.ImageUtils.loadTexture( 'texturas/cara1.jpg' ) })
    	
	];

    // criar grupo geral
    
    group = new THREE.Object3D();
      
    // criar um material Phong para mostrar a iluminação com base no mapa da textura    
    var cauda_material = new THREE.MeshPhongMaterial({ map: map_cauda });
    var corpo_material = new THREE.MeshPhongMaterial({ map: map_corpo });
    var corno_material = new THREE.MeshPhongMaterial({ map: map_corno });
    var cauda_vermelha_material = new THREE.MeshPhongMaterial({ map: map_cauda_v });
    var hoof_material = new THREE.MeshPhongMaterial({ map: mapHoof });

    // chamada das funcoes, permite criar as pernas, cauda, corpo, cornos e cabeca da figura
    // pernas
    var figura_pernas = pernas(corpo_material,hoof_material);
    
    // cauda
    var figura_cauda = cauda(cauda_material,cauda_vermelha_material);

    // corpo
    var figura_corpo = corpo(corpo_material);

    // corno
    var figura_cornos = cornos(corno_material);
    
    // cabeca
    var figura_cabeca = cabeca(corpo_material,cara_materials);
    

    // adicionar ao grupo geral
 	group.add(cornos);
    group.add(figura_cabeca);
    group.add(figura_cornos);
    group.add(figura_pernas);
    group.add(figura_corpo);
    group.add(figura_cauda);


    // juntar grupo a scen
    scene.add(group);
    
    this.setObject3D(group);  
    window.addEventListener( 'resize', reSize, false );
    
}

TweenApp.prototype.handleMouseUp = function(x, y) {
    this.animar.animate();
}

// animar
Animacao.prototype.animate = function() {
    
    var newpos;
    if (this.object3D.position.x > 0) {
        newpos = this.object3D.position.x - 3.0;
    } else {
        newpos = this.object3D.position.x + 3.0;
    }
    
    new TWEEN.Tween(this.object3D.position)
    .to( {
        x: newpos
    }, 1).start();
     
     new TWEEN.Tween(this.object3D.rotation)
    .to( {
        y: newpos
    }, 2000).start();
}