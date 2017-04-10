    
    // desenhar elipse
    function drawEllipse(c,cx,cy,width,height,i)
    {
        c.beginPath();
        c.moveTo(cx, cy - height/2); // começa no ponto mais a acima
        
        if(i == 0 || i == 1)
            c.bezierCurveTo(cx + width/2, cy - height/2, cx + width / 2, cy + height / 2, cx, cy + height / 2);

        if ( i == 0 )
            c.bezierCurveTo(cx - width/2, cy + height/2, cx - width/2, cy - height/2, cx, cy - height/2);

        c.closePath();
    }

    // desenhar triangulo
    function drawTriangle(c,x1,y1,x2,y2,x3,y3)
    {
    	c.beginPath();
    	c.moveTo(x1,y1);
    	c.lineTo(x2,y2);
    	c.lineTo(x3,y3);
    	c.lineTo(x1,y1);
    	c.closePath();
    }

    // desenhar um quadrilatero
    function drawQuadrilateral(c,x1,y1,x2,y2,x3,y3,x4,y4)
    {
    	c.beginPath();
    	c.moveTo(x1,y1);
    	c.lineTo(x2,y2);
    	c.lineTo(x3,y3);
    	c.lineTo(x4,y4);
    	c.lineTo(x1,y1);
    	c.closePath();
    }

    function background(c)
    {
        c.fillStyle = "white";
        c.fillRect(0,0,640,464);

        var gradient = c.createLinearGradient(11,11,0,442);
        gradient.addColorStop(0,"rgb(232,225,206)");
        gradient.addColorStop(0.5,"rgb(240,233,215) ");
        gradient.addColorStop(1,"rgb(232,225,206)");
        c.fillStyle=gradient;
        c.fillRect(10,10,621,445);

        c.fillStyle = "rgba(233,225,214,0.6)"; 
        c.fillRect(78,48,487,384);

        c.fillStyle = gradient;
        c.fillRect(89,59,463,347);
        
        c.save();
        //duas figuras mais a cima coladas a tela branca
        c.fillStyle = "rgb(227,220,194)"
        c.translate(136,10);
        drawInBackground(c,0,0,0); // primeira figura
        c.fill();
        

        c.translate(316,0);
        drawInBackground(c,0,0,1); // segunda figura
        c.fill();
        c.restore();
    }   

    function drawInBackground(c,i)
    {
        c.beginPath();

        if ( i == 0 ) // x = 136 y = 10
        {
            c.moveTo(0,0);
            c.lineTo(0,5);
            c.lineTo(-9,5);
            c.lineTo(-9,16);
            c.lineTo(29,16);
            c.lineTo(29,16);
            c.lineTo(31,13);
            c.lineTo(37,13);
            c.lineTo(37,15);
            c.lineTo(39,15);
            c.lineTo(39,6);
            c.lineTo(41,0);
        }
        else
        {
            c.moveTo(0,0); // x = 452 y = 10
            c.lineTo(0,14);
            c.lineTo(2,14);
            c.lineTo(2,10);
            c.lineTo(5,10);
            c.lineTo(5,14);
            c.lineTo(6,14);
            c.lineTo(25,10);
            c.lineTo(25,5);
            c.lineTo(17,3);
            c.lineTo(17,0);
        }
        c.closePath();
    }

    function yellowBuilding(c,x,y)
    {
        c.save();
        c.translate(x,y);

        c.fillStyle ="rgb(232,202,72)";
        c.fillRect(1,13,31,129);
        c.fillStyle = "rgb(239,232,216)";
        c.fillRect(15,41,13,111); 
        c.fillStyle = "rgb(232,202,72)";
        c.fillRect(28,41,4,106);

        // rectangulos amarelos colados aos rectanguos azuis claros pequenos  
        c.fillRect(34,52,2,25); 
        c.fillRect(34,86,2,25);
        c.fillRect(34,117,2,25);
        //

        drawInYellowBuilding(c); // parte superior do edificio
        c.fill();

        c.fillStyle = "rgb(239,232,216)";
        drawQuadrilateral(c,33,19,59,19,59,9,33,16,33,19);
        c.fill();

        c.save();

        // rectangulos azuis claro por cima do rectangulo preto
        c.translate(36,22);
        c.fillStyle = "rgb(148,183,205) ";
        c.fillRect(0,0,4,20);
        c.fillRect(7,0,5,20);
        c.fillRect(17,0,5,20);
        //

        c.restore();

        // rectangulo preto
        c.fillStyle = "rgb(17,17,17) ";
        c.fillRect(32,32,30,15);

        c.restore();
    }
    // x = 321 y = 205
    function drawInYellowBuilding(c)
    {
        c.beginPath();
            c.moveTo(1,13);
            c.lineTo(28,2);
            c.lineTo(28,11);
            c.lineTo(38,11); 
            c.lineTo(38,0);
            c.lineTo(65,0);
            c.lineTo(63,3);
            c.lineTo(45,3);
            c.lineTo(45,9); 
            c.lineTo(55,8); 
            c.lineTo(71,3); 
            c.lineTo(70,5); 
            c.lineTo(62,8);
            c.lineTo(62,32);        
            c.lineTo(1,32);
            c.lineTo(1,13);   
        c.closePath();
    }

     // x = 301 y = 166
    function redBuilding(c,x,y)
    {
        c.save();
        c.translate(x,y);
        c.fillStyle = "rgb(206,43,34)";
        c.fillRect(7,33,40,130);
        c.fillRect(14,15,63,18); 

        c.fillStyle = "rgb(232,202,72)"; //rectangulo amarelo conectado ao edificio
        c.fillRect(-1,95,8,38);

        c.fillStyle = "rgb(17,17,17) ";
        c.fillRect(7,133,3,30); 

        c.fillStyle = "rgb(239,232,216)";
        c.fillRect(7,133,3,19);
        c.fillRect(13,66,30,89);

        c.fillStyle = "rgb(206,43,34)";
        drawInRedBuilding(c);
        c.fill();

        c.fillStyle = "rgb(239,232,216)";
        c.fillRect(48,17,6,6);

        c.fillStyle = "rgb(51,88,133)";
        c.fillRect(29,40,11,4);
        c.restore();
    }

    // x = 301 y = 166
    function drawInRedBuilding(c) 
    {
        c.beginPath();
        c.moveTo(7,37);
        c.lineTo(0,37);
        c.lineTo(0,28); 
        c.lineTo(5,28);  
        c.lineTo(5,24);  
        c.lineTo(14,24); 
        c.lineTo(14,10);
        c.lineTo(29,10); 
        c.lineTo(29,6);  
        c.lineTo(22,6);
        c.lineTo(22,0);
        c.lineTo(29,0);
        c.lineTo(29,3);  
        c.lineTo(43,3);  
        c.lineTo(43,6);
        c.lineTo(51,6); 
        c.lineTo(51,1);
        c.lineTo(56,1);
        c.lineTo(56,7);
        c.lineTo(77,7);
        c.lineTo(77,11);
        c.lineTo(46,11);
        c.lineTo(46,15); 
        c.lineTo(29,15);
        c.lineTo(29,37);
        c.lineTo(7,37);
        c.closePath();
    }

    //  x = 296 y = 318
    function bottomDark(c,x,y)
    {
        c.save();
        c.translate(x,y);
        c.fillStyle = "rgb(17,17,17) ";
        drawInBottomDark(c); // base
        c.fill();

        // rectangulos no interior
       
        c.fillStyle = "rgb(227,220,194)";
        c.fillRect(15,24,2,8);
        c.fillRect(29,32,3,10);
        c.fillRect(43,48,6,21); 
        c.fillRect(46,84,40,3);
        c.restore();
    }

    // x = 296 y = 318
    function drawInBottomDark(c)
    {
        c.beginPath();
        c.moveTo(0,0);
        c.lineTo(56,0); 
        c.lineTo(56,58); 
        c.lineTo(60,58);
        c.lineTo(60,41); 
        c.lineTo(64,41);
        c.lineTo(64,59);
        c.lineTo(88,86);
        c.lineTo(46,86);
        c.lineTo(7,20);
        c.lineTo(0,20);
        c.lineTo(0,0);
        c.closePath();
    }
    
    function blueBuilding(c)
    {
        shapesAboveBlueBuilding(c,395,219); //figuras azuis claras por cima do edificio

        c.fillStyle = "rgb(51,88,133)";
        drawInBlueBuilding(c); // estrutura inicial
        c.fill();
       
        c.fillRect(440,194,29,3);
        c.fillRect(436,191,4,38);
        c.fillRect(420,205,20,4);
        c.fillRect(420,205,4,32);

        c.fill();

        c.fillStyle = "rgb(239,232,216)";
        drawTriangle(c,509,205,525,205,525,220); // triangulo interior
        c.fill();

        //rectangulo preto interior
        c.fillStyle = "rgb(20,24,25) ";
        c.fillRect(468,200,16,35);

        //rectangulo preto mais a direita
        c.fillRect(538,263,5,19);

        //rectangulo interior composto por dois rectangulos ( azul e branco )
        c.fillStyle = "rgb(239,232,216)";
        c.fillRect(443,242,69,21);
        c.fillStyle = "rgb(51,88,133)";
        c.fillRect(466,245,18,19);

        //3 rectangulos mais a esquerda ao nivel da figura branca e azul
        c.fillRect(388,248,7,18);
        c.fillRect(399,248,8,18);
        c.fillRect(415,248,8,18);

        //2 rectangulos azuis por cima do edificio
        c.fillRect(504,159,4.5,8);
        c.fillRect(500,153,8.5,2.5);

        c.save();
        c.translate(454,296);
        c.fillStyle ="rgb(51,88,133)";
        c.fillRect(0,0,41,44);    //quadrado azul conectado ao edificio
        c.fillRect(0,54,41,34);  //quadrado azul por baixo do quadrado conectado ao edificio
        c.restore();

        shapesAroundBlueBuilding(c,524,242); //figuras azuis claras a volta excepto as por cima do edificio azul (essas fazem parte da funcao shapesAboveBlueBuilding)
        blueBuildingMostLeftShape(c,373,285);//as duas figuras (azul e azul clara) mais a esquerda
    }

     // x = 395 y = 219
    function shapesAboveBlueBuilding(c,x,y)
    {
        c.save();
        c.translate(x,y);

        //trapezio e triangulo a esquerda "coladas" ao edificio amarelo
        //correspondem as duas formas geometricas (triangulo e trapezio) mais a direita do edificio amarelo

        c.fillStyle = "rgb(148,183,205) ";
        
        c.save();
        c.translate(-10,-37);
        drawQuadrilateral(c,0,0,0,28,6,26,6,8);
        c.fill();
        c.restore();

        c.save();   
        c.translate(-1,-24);
       	drawTriangle(c,0,0,0,13,7,11);
        c.fill();
        c.restore();
        //
        //restantes figuras por cima do edificio
        c.fillRect(0,0,4,20);
        
        c.translate(11,-27); 
        c.fillRect(0,0,6,40);
        c.fillRect(0,31,18,19);
        c.fillRect(-9,-12,7,13);
        c.fillRect(0,-1,30,4);
        c.fillRect(12,-25,4,21);

        c.translate(25,-17) 
        c.fillRect(0,0,3.5,17);
        c.fillRect(0,-1,55,4);
        c.fillRect(9,7,12,13);
        c.fillRect(26,-22,4,22);
        c.fillRect(37,-16,3,15);
        c.fillRect(93,3,11,7);

        c.restore();
    }

    function drawInBlueBuilding(c,i)
    {
        c.beginPath();
            c.moveTo(504,384);
            c.lineTo(536,384);
            c.lineTo(536,263);
            c.lineTo(524,263);
            c.lineTo(524,242);
            c.lineTo(536,242);
            c.lineTo(536,188);
            c.lineTo(509,188);
            c.lineTo(509,182); 
            c.lineTo(452,182);
            c.lineTo(452,185);
            c.lineTo(484,185);
            c.lineTo(484,188);
            c.lineTo(474,188);      
            c.lineTo(440,229);
            c.lineTo(438,226);
            c.lineTo(424,233);
            c.lineTo(420,237);
            c.lineTo(409,224);
            c.lineTo(385,242);
            c.lineTo(434,242);
            c.lineTo(434,264);
            c.lineTo(379,264);
            c.lineTo(379,257);
            c.lineTo(373,257);
            c.lineTo(373,285);  
            c.lineTo(400,285); 
            c.lineTo(440,291);
            c.lineTo(444,291);
            c.lineTo(444,283);
            c.lineTo(499,283); 
            c.lineTo(499,335);
            c.lineTo(495,335);
            c.lineTo(495,340);
            c.lineTo(504,340);
            c.lineTo(504,384); 
        c.closePath();
    }

    function drawShape(c)
    {
        c.beginPath();
        c.moveTo(0,0);
        c.lineTo(12,0);
        c.lineTo(12,5);
        c.lineTo(25,5);
        c.lineTo(25,18);
        c.lineTo(37,29);
        c.lineTo(37,36);
        c.lineTo(22,36);
        c.lineTo(22,18);
        c.lineTo(0,0);
        c.closePath();
    }
    // x = 524 y = 242
    function shapesAroundBlueBuilding(c,x,y)
    {
        c.save();
        c.translate(x,y);
        c.fillStyle = "rgb(148,183,205) ";
        c.fillRect(0,0,6,21); // rectangulo azul claro mais a direita
        c.restore();

        //rectangulos azuis claro por baixo do edificio azul
        c.fillStyle = "rgb(148,183,205) ";
        c.fillRect(442,296,12,81);
        c.fillRect(424,294,13,39);
        c.fillRect(424,343,13,42);
        c.fillRect(437,377,5,8);
        c.fillRect(407,292,11,37);
        c.fillRect(407,337,11,39);
        c.fillRect(393,290,9,33);
        c.fillRect(393,332,9,35);

        c.save();
        c.translate(356,257);
        c.fillStyle = "rgb(148,183,205) ";

        //rectangulos azuis claro mais a esquerda do edificio azul
        // primeiro par
        c.fillRect(0,0,4,25);
        c.fillRect(8,0,4,28);

        //segundo par
        c.fillRect(0,34,4,25);
        c.fillRect(8,34,4,29);
            
        //terceiro par
        c.fillRect(0,65,4,29);
        c.fillRect(8,68,4,29);

        c.fillRect(8,106,4.5,14.5);

        var newY = 25+9+25+6+29;
        c.save();
        c.translate(0,94);

        c.fillStyle = "rgb(148,183,205) ";
        drawShape(c); //figura azul clara mais a esquerda e mais a baixo do edificio
        c.fill();

        c.restore();
        c.restore();

    }

    function blueBuildingMostLeftShape(c,x,y)
    {
        c.save();
        c.translate(x,y);
        //figura azul
        c.fillStyle = "rgb(51,88,133)";
        c.fillRect(0,10,16,27);
        c.fillRect(6,3,11,34);
        c.fillRect(6,0,2,34);
        c.restore();

        var newY = y + 37;
        
        //figura azul clara
        c.save();
        c.translate(x,newY);
        c.fillStyle = "rgb(148,183,205)";
        c.fillRect(0,11,17,24);
        c.fillRect(6,6,11,24);

        c.restore();
    }

    // x = 112 y = 243
    function  lightblueBuilding_p1(c,x,y)
    {
        c.save();
        c.translate(x,y);

        c.fillStyle = "rgb(148,183,205) ";
        
        // primeira fila
        c.fillRect(0,0,7,38);
        c.fillRect(11,0,14,38);
        c.fillRect(43,0,24,38);
        c.fillRect(81,0,24,38);

        // segunda fila
        c.fillRect(0,50,7,48);
        c.fillRect(11,50,15,48);
        c.fillRect(43,50,24,44);
        c.fillRect(81,50,23,44);

        //terceira fila
        c.fillRect(0,105,7,41);
        c.fillRect(-8,142,15,4);
        c.fillRect(12,105,14,41);
        c.fillRect(44,109,24,41);

        //figuras pretas
        c.fillStyle = "rgb(17,17,17) ";
        c.fillRect(81,105,23,36);
        c.fillRect(44,147,24,6);
        c.fillRect(68,153,21,7);
        c.fillRect(40,153,7,5);
        c.restore();
    }

    // x = 99 y = 164
    function lightblueBuilding_p2(c,x,y)
    {
        c.save();
        c.translate(x,y);

        c.fillStyle = "rgb(17,17,17) ";
        c.fillRect(0,1,46,30);  // figura preta mais a esquerda e mais a acima

        c.fillStyle = "rgb(148,183,205) ";
        drawInLightBlueBuilding(c,0); // base do telhado
        c.fill();

        c.fillStyle = "rgb(239,232,216)"; // detalhe no interior
        c.fillRect(49,3,8,4);
        c.fillRect(79,26,17,3);

        c.fillStyle = "rgb(17,17,17) "; // detalhe no interior
        c.fillRect(79,44,20,18);

        // a maior figura preta no interior
        c.fillRect(30,26,23,36);
        drawQuadrilateral(c,30,62,69,62,69,73,41,73);
        c.fill();

        c.fillRect(44,-30,1,1);
        
        c.fillStyle = "rgb(148,183,205) "; // rectangulos azuis claro a volta
        c.fillRect(46,-28,5,15);
        c.fillRect(45,-47,2,15);
        c.fillRect(70,-5,10,3)
        c.restore();
    }

    //x = 213 y = 170
    function lightbluebuilding_p3(c,x,y)
    {   
        c.save();
        c.translate(x,y);

        c.fillStyle = "rgb(148,183,205) ";
        // desenha a base do centro
        drawInLightBlueBuilding(c,2);
        c.fill();

        // detalhes ( rectangulos no interior )

        c.fillStyle = "rgb(239,232,216)";
        c.fillRect(29,-1,4,23);
        c.fillRect(39,-1,4,23);
        c.fillRect(47,-1,4,27);
        c.fillRect(24,4,2,13);
        c.fillRect(4,15,4,19);
        c.fillRect(13,25,6,7);

        // rectangulo na diagonal entre o edificio vermelho e este
        c.save();
        c.translate(95,32);
        c.rotate(- Math.PI / 5);
        c.fillRect(-15,-3,25,4);
        c.restore();
        // 

        //rectangulo mais a esquerda e mais acima
        c.fillStyle = "rgb(148,183,205) ";
        c.fillRect(-14,-11,24,5);
        c.fillRect(3,-7,7,6);

        c.restore();
    }

    function drawInLightBlueBuilding(c,i)
    {
        c.beginPath();
        if (i == 0)
        {
            c.moveTo(0,79); 
            c.lineTo(0,29); 
            c.lineTo(35,14); 
            c.lineTo(35,0);
            c.lineTo(41,0);
            c.lineTo(41,11);
            c.lineTo(46,9); 
            c.lineTo(46,1);
            c.lineTo(80,1);
            c.lineTo(80,8);
            c.lineTo(149,73); 
            c.lineTo(41,73);
            c.lineTo(30,62);
            c.lineTo(25,66); 
            c.lineTo(38,79);
            c.lineTo(0,79);
        }
        else
        {
            c.moveTo(-1,38);
            c.lineTo(-1,3);
            c.lineTo(12,3);
            c.lineTo(12,15);
            c.lineTo(21,15);
            c.lineTo(21,-1);
            c.lineTo(57,-1); 
            c.lineTo(57,15);
            c.lineTo(66,15); 
            c.lineTo(66,32); 
            c.lineTo(95,32); 
            c.lineTo(95,39); 
            c.lineTo(88,39);
            c.lineTo(88,47);
            c.lineTo(95,47);
            c.lineTo(95,57);
            c.lineTo(87,57);
            c.lineTo(87,144);
            c.lineTo(75,144);
            c.lineTo(75,69);
            c.lineTo(53,69);
            c.lineTo(53,43);
            c.lineTo(35,43);
            c.lineTo(35,67);
            c.lineTo(24,67);
            c.lineTo(24,43);
            c.lineTo(-1,43);
            c.lineTo(-1,38);
        }
        c.closePath();
    }

    // x = 241 y = 234
    function centralDark_p1(c,x,y)
    {
        c.save();
        c.translate(x,y);

        // estrutura inicial
        c.fillStyle = "rgb(17,17,17) ";
        drawInCentralDark(c); 
        c.fill();

        c.fillStyle = "rgb(239,232,216)";
        c.fillRect(0,44,4,8); 
        //

        //figura azul claro mais a baixo
        c.fillStyle = "rgb(148,183,205)";
        drawQuadrilateral(c,1.5,158,33,158,36,161,1.5,161);
        c.fill();

        c.restore();
    }
    // x = 261 y = 202
    function centralDark_p2(c,x,y)
    {
        c.save();
        c.translate(x,y);
    
        c.fillStyle = "rgb(17,17,17) ";
        drawTriangle(c,0,0,27,94,0,94);
        c.fill();
        c.fillRect(-3,37,3,9);
        c.fillRect(-8,81,5,13);
        c.fillRect(-3,87,3,7);
        c.fillRect(22,94,13,18);
        c.fillRect(9,30,14,8);
        c.fillRect(3,98,8,10);
        c.fillRect(17,125,4,20);
        c.fillRect(23,125,6,20);
        c.restore();
    }
    //funcao para desenhar as figuras pretas que estao no centro
    //excepto o que esta "colado" ao edificio vermelho e amarelo essa parte e' desenhada na funcao bottomDark
    function drawInCentralDark(c)
    {
        c.beginPath();
            c.moveTo(0,0);
            c.lineTo(0,156);
            c.lineTo(30,156);
            c.lineTo(16,142); 
            c.lineTo(16,119);
            c.lineTo(7,119);
            c.lineTo(7,62);
            c.lineTo(10,62);
            c.lineTo(10,46);
            c.lineTo(7,46);
            c.lineTo(7,0);
            c.lineTo(0,0);
        c.closePath();
    }
    function drawInAboveRedBuilding_p1(c,i)
    {
        c.beginPath();
        if(i == 0)
        {
            c.moveTo(0,0);
            c.lineTo(15,-38);
            c.lineTo(27,-16);
            c.lineTo(36,-40);
            c.lineTo(32,-40);
            c.lineTo(32,-38);
            c.lineTo(35,-38); 
            c.lineTo(40,-47);
            c.lineTo(51,-25);
            c.lineTo(57,-25);
            c.lineTo(61,-28);
            c.lineTo(61,-40);
            c.lineTo(70,-40);
            c.lineTo(70,-43); 
            c.lineTo(45,-43);
            c.lineTo(45,-46);
            c.lineTo(62,-46);
            c.lineTo(62,-49);
            c.lineTo(52,-49);
            c.lineTo(52,-57);
            c.lineTo(62,-57);
            c.lineTo(62,-72);
            c.quadraticCurveTo(70,-61,70,-53);
            c.quadraticCurveTo(73,-53,74,-49);
            c.lineTo(74,-22);
            c.lineTo(72,-22);
            c.lineTo(72,-25);
            c.lineTo(70,-22);
            c.lineTo(54,-13);
            c.lineTo(50,-19);
            c.lineTo(45.7,-16.7); 
            c.lineTo(49.7,-10.7);
            c.lineTo(41,-3);
            c.lineTo(41,0);
            c.lineTo(37,0);
            c.lineTo(33,4);
            c.lineTo(33,21);
            c.lineTo(30,21);
            c.lineTo(30,9);
            c.lineTo(25,9);
            c.lineTo(25,31);
            c.lineTo(17,31);
            c.lineTo(17,33);
            c.lineTo(14,33);
            c.lineTo(14,18);
            c.lineTo(3,18);
            c.lineTo(3,13);
            c.lineTo(13,13);
            c.lineTo(13,0);
            c.lineTo(0,0);
        }

        else if( i == 1 )
        {
            c.moveTo(9,22); // x = 340 y = 120
            c.lineTo(7,22);
            c.quadraticCurveTo(4,22,4,19);
            c.lineTo(4,19);
            c.quadraticCurveTo(4,17,7,17);
            c.lineTo(7,17);
            c.lineTo(10.5,17);
            c.lineTo(10.5,15);
            c.quadraticCurveTo(10.5,11,13,11);
            c.quadraticCurveTo(16,11,16,15);
            c.lineTo(16,22);
            c.lineTo(12,22);
        

        }
        else if( i == 2 )
            c.arc(15.5,24,4.4, 2 * Math.PI,false);
        else if ( i == 3)
        {
            c.moveTo(9.7,45); // x = 338 y = 142
            c.lineTo(10,41);
            c.quadraticCurveTo(10.2,35,15,35);
            c.lineTo(14,35);
            c.quadraticCurveTo(22,36,16,50);
            c.lineTo(16,50);
            c.lineTo(10,53);
            c.quadraticCurveTo(6,56,3,54);
            c.lineTo(3,54);
            c.quadraticCurveTo(1,51,4,49);
            c.lineTo(9.7,45);
        }
        else
        {
            c.moveTo(42.5,-10);
            c.lineTo(42.5,-18);
            c.lineTo(41.5,-19);
            c.lineTo(47,-19);
            c.lineTo(44,-17);
            c.lineTo(45,-14);
            c.lineTo(42.5,-10);
        }

        c.closePath();
    }
    // x = 276 y = 169
    function aboveRedBuilding_p1(c,x,y)
    {
        c.save();
        c.translate(x,y);

        c.fillStyle = "rgb(148,183,205) ";
        drawInAboveRedBuilding_p1(c,0); // estrutura inical
        c.fill();

        c.fillStyle = "rgb(239,232,216)";
        drawTriangle(c,10,-16,23,-16,15,-31); // triangulo 1
        c.fill();
  
        drawTriangle(c,33,-21,49,-21,40,-40); // triangulo 2  
        c.fill();

        c.fillStyle = "rgb(239,232,216)"; // rectangulos no interior
        c.fillRect(7,-10,5,7);
        c.fillRect(14,-14,9,3);
        c.fillRect(15,-8,7,13);
        c.fillRect(16,8,4,5);

         // triangulo + rectangulo no meio dos dois triangulos
        c.fillRect(25,-10,2,15);
        drawTriangle(c,25,-5,37,-5,25,5);
        c.fill();

        c.fillRect(29,-17,12,10); // rectangulo acima da figura anterior ( por baixo do segundo triangulo)

        c.fillStyle = "rgb(232,202,72)"; // figuras amarelas 
        drawQuadrilateral(c,1,-3.9,7,-3.9,7,-6.9,2,-6.9);
        c.fill();
        drawInAboveRedBuilding_p1(c,4);
        c.fill();
        //
        c.fillStyle = "rgb(51,88,133)"; // figuras azuis
        c.fillRect(49,-37,2,8);
        c.fillRect(53.5,-37,4,8);

        // figura azul na diagonal
        drawQuadrilateral(c,12,-23,17,-34,16,-35,11,-24);
        c.fill();

        c.fillStyle = "rgb(148,183,205) ";  
        // figura azul clara mais acima da figura na diagonal
        drawQuadrilateral(c,60,-74,60,-76.5,54,-86.5,54,-84);

        c.fillRect(35,-11,2,4); // figura azul clara no interior do rectangulo por baixo do segundo triangulo
        c.fill();

        //figuras curvas
        c.save();
        c.translate(52,-72);

        c.fillStyle = "rgb(239,232,216)";
        drawInAboveRedBuilding_p1(c,1);
        c.fill();

        drawInAboveRedBuilding_p1(c,2);
        c.fill();

        c.fillStyle = "rgb(51,88,133)";
        c.fillRect(12,48,11,3); // figura azul mais a direita
        
        c.fillStyle = "rgb(239,232,216)";
        drawInAboveRedBuilding_p1(c,3);
        c.fill();
        //
        c.restore();
        c.restore();
    }

    // x = 350 y = 139
    function aboveRedBuilding_p2(c,x,y)
    {
        c.save();
        c.translate(x,y);

        c.fillStyle = "rgb(232,202,72)";
        drawInAboveRedBuilding_p2(c,0); // parte amarela conectada a parte azul clara e esferas
        c.fill();

        drawEllipse(c,14,0,19,25,0); //elipse amarela
        c.fill();

        //restantes partes amarelas 
        c.fillRect(16.5,15,7,8);
        c.fillRect(20.5,23,6,4);
        c.fillRect(-18,18,7,5);
        //

        c.fillStyle = "rgb(233,226,208)";
        drawEllipse(c,5.5,7,7,8,0); // elipse no interior da elipse amarela
        c.fill();

        drawEllipse(c,14,0,15,15,0);  // elipse no interior da parte desenhada em drawInAboveRedBuilding_p2(c,0);
        c.fill();

        c.fillStyle = "rgb(148,183,205)";
        drawEllipse(c,14,0,23,25,1); // elipse azul clara
        c.fill();

        c.fillRect(20.5,27.5,15,4); 

        drawInAboveRedBuilding_p2(c,1); // figura azul clara conectada a esfera azul clara
        c.fillRect(3,21,5,2.5)
        c.fillRect(-10,22.5,3,6.5);
        c.fill();

        c.fillStyle = "rgb(232,202,72)";
        drawInAboveRedBuilding_p2(c,2); 
        c.fill();


        c.lineWidth = 1 / 2;
        c.strokeStyle =  "rgb(232,202,72)";
        drawInAboveRedBuilding_p2(c,3); // figura que conecta o rectangulo amarelo mais a baixo a figura desenhada em drawInAboveRedBuilding_p2(c,0);
        c.fill();
        c.stroke();
        
        c.fillStyle = "rgb(233,226,208)";
        drawEllipse(c,18,0,8,11,0); // elipse no interior da elipse azul clara
        c.fill();

        c.fillStyle = "rgb(51,88,133)";
        c.fillRect(3,14,5,5); // rectangulo azul claro

        c.restore();
    }

    function drawInAboveRedBuilding_p2(c,i)
    {
        c.beginPath();
        if (i == 0)
        {
            c.moveTo(-1,1);
            c.lineTo(15,1);
            c.lineTo(15,11);
            c.quadraticCurveTo(8,11,8,16);
            c.lineTo(2.5,16);
            c.lineTo(2.5,17);
            c.quadraticCurveTo(2.5,4,-3.5,14);
            c.lineTo(-3.5,10);
            c.lineTo(-4,10);
            c.lineTo(-4,8);
            c.lineTo(-1,8);
            c.lineTo(-1,1);
        }
        else if ( i == 1 )
        {
            c.moveTo(14,12);
            c.quadraticCurveTo(15,12,15,16);
            c.quadraticCurveTo(15,22,3,22);
            c.lineTo(3,23);
            c.lineTo(16.5,23);
            c.lineTo(16.5,8);
            c.lineTo(14,8);
            c.lineTo(14,13);
        }
        else if ( i == 2 )
        {
            c.moveTo(-13,23);
            c.lineTo(-4,23);
            c.lineTo(-4,20);
            c.lineTo(-7,22);
            c.lineTo(-13,23);
        }
        else
        {
            c.moveTo(-11,18);
            c.lineTo(-3.5,13);
            c.lineTo(-11,18);
        }       
        c.closePath();
    }

    
    function main()
    {
        var canvas = document.getElementById("quadro");
        var ctx = canvas.getContext("2d");
        
        //background
        background(ctx);

        // parte preta conectada ao edificio amarelo e edificio vermelho
        bottomDark(ctx,296,318);
    
        // edificios
        // azul
        blueBuilding(ctx,536,384); //e redores do edificio azul
        
        // vermelho
        redBuilding(ctx,301,166);

        // amarelo
        yellowBuilding(ctx,320,205);

        // azul claro  - 3 partes

        lightblueBuilding_p1(ctx,112,243);  // figuras por baixo do telhado
        lightblueBuilding_p2(ctx,99,164);   // telhado
        lightbluebuilding_p3(ctx,213,170);  // figura mais ao centro ao nivel do edificio vermelho

        //partes pretas no centro do quadro a excepcao do que esta "colado" ao edificio amarelo e vermelho. isso faz parte da funcao bottomDark
        centralDark_p1(ctx,241,234); //parte que esta conectada ao edificio azul claro
        centralDark_p2(ctx,261,202); //parte que se sobrepoe ao edificio azul claro e esta ao lado de centralDark_p1

        //referente a parte mais acima do quadro, ou seja, por cima do edificio vermelho
        aboveRedBuilding_p1(ctx,276,169); //toda a parte azul clara acima do edificio vermelho excepto as partes curvas mais a direita
        aboveRedBuilding_p2(ctx,351,140); //contem a parte mais a direita (mistura de azul e amarelo)

        // baixar a nitidez do quadro
        ctx.fillStyle = "rgba(232,225,206,0.05)";
       	ctx.fillRect(88.5,58.5,463,347);
    }
