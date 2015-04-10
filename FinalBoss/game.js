var stage = 0;
var queue = 0;
var FPS = 60;
var gameTimer = 0;
var frameCount = 0;
var mouseX = 0, mouseY = 0;

var SCREEN_WIDTH = 800;
var SCREEN_HEIGHT = 600;

var KEYCODE_J = 74;
var KEYCODE_M = 77; 
var KEYCODE_W = 87;
var KEYCODE_A = 65;
var KEYCODE_S = 83;
var KEYCODE_D = 68;
var KEYCODE_I = 73;
var KEYCODE_K = 75;
var KEYCODE_G = 71;
var KEYCODE_ENTER = 13;


//----------------------------IMG Variables----------------------------------//
var imgGameBackground = 0, imgMainMenu = 0, imgCredits = 0, imgInstructions = 0, imgVictory = 0,  imgDefeat = 0, imgShop = 0, imgSpellsItems = 0, imgDescription = 0, imgBattleMenu = 0;
//---------------------------Sound Variables---------------------------------//
var soundButtonOver = 0, soundButtonClicked = 0, soundDrinkPotion = 0, soundAttack = 0, soundDie = 0;
//----------------------------BTN Variables----------------------------------//
var buttonSheet;
var creditButtonSheet;
//---------------------------------------------------------------------------//

manifest = [
    {src:"gameareabackground01.png", id:"bg1"},
	{src:"gameareabackground02.png", id:"bg2"},
	{src:"gameareabackground03.png", id:"bg3"},
	{src:"gameareabackground04.png", id:"bg4"},
	{src:"gameareabackground05.png", id:"bg5"},
	{src:"gameareabackground06.png", id:"bg6"},
	{src:"gameareabackground07.png", id:"bg7"},
    {src:"spellsitemswindow.png", id:"spellsItems"},
    {src:"gameovervictory.png", id:"victory"},
    {src:"gameoverdefeat.png", id:"defeat"},
    {src:"battlewindows.png", id:"battle"},
    {src:"instructions.png", id:"instructions"},
    {src:"descwindow.png", id:"description"},
    {src:"shopwindow.png", id:"shop"},
    {src:"mainmenu.png", id:"mainMenu"},
    {src:"credits.png", id:"credits"},
	{src:"sword.png", id:"sword"},
    {src:"350wideWindow100.png", id:"basicWindow100"},
    {src:"350wideWindow90.png", id:"basicWindow90"},
    {src:"350wideWindow80.png", id:"basicWindow80"},
	{src:"ItemShop.png", id:"itemShop"},
    {src:"buttonOver.ogg", id:"buttonOver"},
    {src:"buttonPressed.ogg", id:"buttonPressed"},
    {src:"fireball.png", id:"fireball"},
	{src:"slash.png", id:"slash"},
    {src:"Selector.png", id:"arrow"},
	{src:"Buttons.png", id:"buttons"},
    {src:"creditbutton.png", id:"credbutton"},
	{src:"box.png", id:"box"},
	{src:"health.png", id:"health"},
	{src:"rock.png", id:"rock"},
	{src:"bolt.png", id:"bolt"},
	{src:"deathSmoke.png", id:"death"},
	{src:"badarcher.png", id:"archer"},
	{src:"warrior.png", id:"warrior"},
	{src:"mageExport.png", id:"mage"},
	{src:"smallBossExport.png", id:"skullSheet"},
	{src:"bigBossExport.png", id:"bigBossSheet"},
	{src:"potionDrink.ogg", id:"drinkPotion"},
    {src:"deathScream.ogg", id:"deathScream"},
    {src:"attackSound.ogg", id:"attackSound"},
];


var gameState = {
    MAINMENU:0,
    INSTRUCTIONS:1,
    CREDITS:2,
    GAME:3,
    VICTORY:4,
    DEFEAT:5,
}

var classes = {
    ADVENTURER:0, //Default
    WARRIOR:1, //More dmg + HP + def, low mp
    ROUGE:2, //More dmg, avg mp, less hp
    MAGE:3, //low HP, low def, high mp, low dmg, high mDmg
    RANGER:4, //Avg dmg, avg hp, avg mp, low def
}

var items = {
    STEROIDS:"Steroids",
}

var minions = {
    SLIME:0, //x damage to single hero; 10 cost
}

var traps = {
    BOULDER:0, //x damage to up to 2 heroes; 15 cost
    SPIKES:1, //X damage to single hero; 10 cost
}

var spells = {
    FIRE:"Fire", //chance of burn, high-ish damage
    THUNDER:"Thunder", //chance of paralysis
    HEAL:"Heal", //single heal. Maybe AoE heal later?
}

var skills = {
    STEAL:"Steal",
}

var debuff = {
    BURN:"Burn",
    ZAP:"Zap",
}

var buff = {
    ATTACKBOOST:"Attack Boost",
    DEFENSEBOOST:"Defense Boost",
}

/*
Heroes should have:
    ✓ alive (bool)
    ✓ maxHP
    ✓ hp
    ✓ maxMP
    ✓ mp
    ✓ Physical Attack
    ✓ Physical Defense
    ✓ Magical Attack
    ✓ Magical Defense
    ✓ Speed
    ATB Gauge
    
    ✓List of Spells/Skills
    
    ✓Item/List of Items
    
    ✓status effect?
*/

//--------------------------- Emmanuel Section ------------------------------//

var party = [];
var allAbilities = [];
var attackParticle; 

function getAbility(name)
{
	for(i=0; i<allAbilities.length;i++)
	{
		if(allAbilities[i].name == name)
		{
			return allAbilities[i];
		}
	}
}

function setupParty(stage) {
    //switch, current stage for final
    //single setup for alpha
    var hero1 = new createHero();
	var hero2 = new createHero();
	var hero3 = new createHero();
    hero1.initialize(classes.WARRIOR, 3*(currentLevel+1), 0);
    hero2.initialize(classes.MAGE, 3*(currentLevel+1), 1);
    hero3.initialize(classes.RANGER, 3*(currentLevel+1), 2);
	
	attackParticle = new scaleParticle("slash", gameContainer, 500);
}

//choices in a turn:
/*
Attack
Cast Spell
Use Item
*/

//Cast a spell every 3/4/5th turn?
//Use item if below x% health

function heroUpdate(dt) {
    for(i = 0; i < party.length; i++) {
        var currentHero = party[i];
        
        if(currentHero.alive) {
            if(currentHero.go) {
                chooseAction(currentHero);
            }
        }
    }
}

function chooseAction(hero) {
}

//flat damage reduction? % based?
function attack(attacker, defender) {
	progressHalted = true;
    var damage = attacker.attackPhys;
    var defense = defender.defensePhys;
    
    var minDmg = damage/4; //min 25% dmg
    
    var finalDamage = damage - defense;
    finalDamage = Math.ceil(finalDamage);
    minDmg = Math.ceil(minDmg);
    if(finalDamage < minDmg) {
        finalDamage = minDmg;
    }
	attackParticle.initialize(new vec2(defender.graphic.x, defender.graphic.y));
	attackParticle.onComplete = function()
	{
		  soundAttack = new createjs.Sound.play(queue.getResult("attackSound").src);
		new lerp(attacker.pos, attacker.graphic, .05, .02, function(){progressHalted = (itemShopContainer.visible);receiveDamage(defender, finalDamage);});
	}
    
}

function attemptSpellCast(attacker, defender, spellType) {
    if(attacker.mp < spellCost) {
        failSpellCast();
    } else {
        castSpell(attacker, defender, spellType);
        attacker.mp -= spellCost;
    }
}

function failSpellCast() {
    //print "You don't have enough mp"
    //go back to select
}

function castSpell(attacker, defender, spellType) {
    var damage = attacker.attackMagic;
    
    if(spellType == spells.HEAL) {
        heal(defender, damage/2);
    } 
    
    else {
        var minDamage = damage/3; //min 33% dmg
		minDamage = Math.ceil(minDamage);
        var defense = defender.defenseMagic;
        
        switch(spellType) {
            case spells.FIRE:
                addStatus(defender, 0.20, debuff.BURN);
                break;
            case spells.THUNDER:
                addStatus(defender, 0.10, debuff.ZAP);
                break;
        }
        
        var finalDamage = damage - defense;
		finalDamage = Math.ceil(finalDamage);
        if(finalDamage < minDamage) {
            finalDamage = minDamage;
        }
        receiveDamage(defender, finalDamage);
    }
}

function addStatus(target, chance, effect) {
    var random = Math.random();
    
    if(random < chance) {
        target.statusEffect = effect;
    }
}

function receiveDamage(target, amount) {
    target.hpCurr -= amount;
	new addMovingText(gameContainer, "-"+amount, target.graphic, 2, 25, "#F00");
    if(target.hpCurr <= 0) {
        death(target);
    }
}

function death(target) {
    soundDie = new createjs.Sound.play(queue.getResult("death").src);
    target.alive = false;
	if(boss != target)
	{
		boss.gold += target.gold;
		boss.exp += target.exp;
		if(boss.exp > boss.expRequired)
		{
			boss.exp = boss.exp - boss.expRequired;
			boss.levelUp();
		}
		selector.pointTo(0);
		selector.pointToNext(true);
		target.graphic.visible = false;
	}
	target.hpCurr = 0;
    //invisible or dead sprite
    //cannot take actions
}

function heal(target, amount) {
    target.hpCurr += amount;
    if(target.hpCurr >= target.hpMax) {
        target.hpCurr = target.hpMax;
    }
}

//------------------------- End Emmanuel Section ----------------------------//

var playCheck;

function viewAbilityList()
{
	if(playCheck)
	{
		abilityListContainer.visible = !abilityListContainer.visible;
		itemListContainer.visible = false;
		selector.graphic.visible = false;
		selector.descript.hide();
	}
}

function viewItemList() 
{
	if(playCheck)
	{
		itemListContainer.visible = !itemListContainer.visible;
		abilityListContainer.visible = false;
		selector.graphic.visible = false;
		selector.descript.hide();
	}
}

function chooseAttack()
{
	if(playCheck)
	{
		abilityListContainer.visible = false;
		itemListContainer.visible = false;
		currentAbility = undefined
		selector.graphic.visible = true;
		selector.descript.show();
	}
		
}

function Selector(image)
{
    this.graphic = new createjs.Bitmap(queue.getResult(image));
    this.graphic.visible = false;
	this.descript = new Description();
	this.descript.initialize(gameContainer, "Choose target(s)");
    this.slot = 0;
    var mode =
	{
		attack: 0,
		cast: 1,
		item: 2,
	};
    this.pointTo = function(slot)
    {
		if(this.graphic.visible)
		{
			this.descript.show();
		}
        this.slot = slot;
         //75 is width of square, change to image width later
        this.graphic.x = party[slot].graphic.x
        this.graphic.y = party[slot].graphic.y - 75;
    }
	
	this.pointToNext = function(down)
	{
		var found = false;
		var curIndex = this.slot;
		while((curIndex < party.length && curIndex >= 0) && !found)
		{
			curIndex += (down)?1:-1;
			if(curIndex >= party.length || curIndex < 0)
			{
				curIndex = this.slot;
				break;
			}
			found = party[curIndex].alive;
		}
		this.pointTo(curIndex);
	}
	
	this.update = function()
	{
		//75 is width of square, change to image width later
        this.graphic.x = party[this.slot].graphic.x;
        this.graphic.y = party[this.slot].graphic.y - 75;
	}
}

var currentAbility;
var currentLevel = 0;
var bigBossGraphic;
var levelImages = [];

function setupCanvas() {
    var canvas = document.getElementById("game"); //get canvas with id='game'
    canvas.width = SCREEN_WIDTH;
    canvas.height = SCREEN_HEIGHT;
    stage = new createjs.Stage(canvas); //makes stage object from the canvas
    stage.enableMouseOver();
}

function main() {
    setupCanvas(); //sets up the canvas
    mouseInit();
    loadFiles(); 
    resetGameTimer();
}

//makes sure DOM is ready then loads main()
if( !!(window.addEventListener)) {
    window.addEventListener ("DOMContentLoaded", main);
}else{ //MSIE
    window.attachEvent("onload", main);
}

function loop() {
    runGameTimer();
    stage.update();
	if(gameContainer != undefined && gameContainer.visible)
	{
		update(1/FPS);
		playCheck = !levelUpContainer.visible && !itemShopContainer.visible && !tutorialContainer.visible;
		var count = 0;
		selector.update();
		for(var i=0; i<party.length; i++)
		{
			count += (party[i].alive)?1:0;
		}
		if(count == 0)
		{
			nextLevel();
		}
		if(boss.alive == false)
		{
			boss.deathAnimation(1/FPS);
		}
	}
}

createjs.Ticker.addEventListener("tick", loop);
createjs.Ticker.setFPS(FPS);

function mouseInit() {
    stage.on("stagemousemove", function(evt) {
        mouseX = Math.floor(evt.stageX);
        mouseY = Math.floor(evt.stageY);
    })
}

function resetGameTimer() {
    gameTimer = 0;
    frameCount = 0;
}

function runGameTimer() {
    frameCount += 1;
    if(frameCount%(FPS/10) === 0) {
        gameTimer = frameCount/(FPS);   
    }
}

var pressed = false;
var toggleOn = false;

function handleKeyDown(evt) {
    if(!evt){ var evt = window.event; }  //browser compatibility
    switch(evt.keyCode) {
        case KEYCODE_J:
			if(!pressed)
			{
				boss.addAbility(getAbility("Death"));   
				toggleOn = !toggleOn;
				if(toggleOn)
				{
					new addMovingText(gameContainer, "Death spell added", new vec2(250, 250), 2, 30, "#000");
				}
				else
				{
					new addMovingText(gameContainer, "Scout's honor not to use the death spell....?", new vec2(250, 250), 2, 30, "#000");
				}
				pressed = true;
			}
			break;
        case KEYCODE_M:     /*console.log(evt.keyCode+" down");*/ return false;
		case KEYCODE_A:
			chooseAttack();
			break;
		case KEYCODE_S:
			viewAbilityList();
			break;
		case KEYCODE_D:
			viewItemList();
			break;
        case KEYCODE_I:
            if(selector.graphic.visible && selector.slot > 0)
            {
                selector.pointToNext(false);
            }
            break;
        case KEYCODE_K:    
         if(selector.graphic.visible && selector.slot < party.length-1)
            {
                selector.pointToNext(true);
            }
            break;
        case KEYCODE_ENTER:
        if(selector.graphic.visible)
        {
			if(currentAbility == null)
			{
				boss.move = function()
				{
					attack(boss, party[selector.slot]);
				}
			}
			else if(currentAbility != null )
			{
				var currAbility = currentAbility;
				boss.move = function()
				{
					boss.cast([party[selector.slot]],currAbility); 
				}
				currentAbility = undefined;
			}
			selector.graphic.visible = false;
			selector.descript.hide();
        }
		break;
		case KEYCODE_G:
			boss.gold += 1000;
			break;
            
    }
} 

function handleKeyUp(evt) {
    if(!evt){ var evt = window.event; }  //browser compatibility
    switch(evt.keyCode) {
        case KEYCODE_J:   
		pressed = false; 
		
		break;
        case KEYCODE_M:     /*console.log(evt.keyCode+" up");*/ break;
    }
}

document.onkeydown = handleKeyDown;
document.onkeyup = handleKeyUp;

var titleContainer;
var instructionsContainer;
var defeatContainer;
var victoryContainer;
var creditContainer;
var gameContainer;
var itemListContainer;
var itemShopContainer;
var bossGoldContainer;
var bossInfoContainer;
var menuContainer;
var heroInfoContainer;
var levelUpContainer;
var abilityListContainer;
var partyContainer;
var tutorialContainer;
var selector;
var itemShop;
var tut;

function createContainers()
{
	for(var i=0; i<stage.children.length; i++)
	{
		stage.removeChild(stage.children[i]);
	}
	titleContainer =  new createjs.Container();
	defeatContainer = new createjs.Container();
	victoryContainer = new createjs.Container();
    creditContainer = new createjs.Container();
	instructionsContainer = new createjs.Container();
    gameContainer = new createjs.Container();
    bossInfoContainer = new createjs.Container();
    menuContainer = new createjs.Container();
    heroInfoContainer = new createjs.Container();
	partyContainer = new createjs.Container();
    abilityListContainer = new createjs.Container();
	levelUpContainer = new createjs.Container();
	itemListContainer = new createjs.Container();
	itemShopContainer = new createjs.Container();
	bossGoldContainer = new createjs.Container();
	tutorialContainer = new createjs.Container();
	
	itemShop = new ItemShop();
    
    stage.addChild(gameContainer);
	stage.addChild(titleContainer);
	stage.addChild(defeatContainer);
	stage.addChild(victoryContainer);
    stage.addChild(creditContainer);
	stage.addChild(instructionsContainer);
	titleContainer.addChild(imgMainMenu);
    gameContainer.addChild(imgGameBackground);
    gameContainer.addChild(bossInfoContainer);
    gameContainer.addChild(menuContainer);
    gameContainer.addChild(heroInfoContainer);
	gameContainer.addChild(partyContainer);
    gameContainer.addChild(abilityListContainer);
	gameContainer.addChild(itemListContainer);
	gameContainer.addChild(levelUpContainer);
	
	selector = new Selector("arrow");
    gameContainer.addChild(selector.graphic);
	defeatContainer.addChild(imgDefeat);
	victoryContainer.addChild(imgVictory);
    creditContainer.addChild(imgCredits);
	instructionsContainer.addChild(imgInstructions);
    selector.graphic.visible = false;
	
	titleContainer.visible = true;
	gameContainer.visible = false;
	defeatContainer.visible = false;
	victoryContainer.visible = false;
    creditContainer.visible = false;
	instructionsContainer.visible = false;
	itemShopContainer.visible = false;
	setupButtons();
}

function setupContainers()
{
	gameContainer.addChild(itemShopContainer);

	var bossInfo = new createjs.Bitmap(queue.getResult("basicWindow100"));
    bossInfo.y = imgGameBackground.image.height - bossInfo.image.height;
    bossInfo.scaleX = 300/bossInfo.image.width;
    bossInfoContainer.addChild(bossInfo);
    var menu = new createjs.Bitmap(queue.getResult("basicWindow100"));
    menu.x = bossInfo.x+bossInfo.image.width*bossInfo.scaleX;
    menu.y = bossInfo.y;
    menu.scaleX = 150/bossInfo.image.width;
    menuContainer.addChild(menu);
    var heroInfo = new createjs.Bitmap(queue.getResult("basicWindow100"));
    heroInfo.x = menu.x + menu.image.width*menu.scaleX;
    heroInfo.y = menu.y;
    heroInfo.scaleX = 350/heroInfo.image.width;
    heroInfoContainer.addChild(heroInfo);
    var spellList = new createjs.Bitmap(queue.getResult("basicWindow80"));
    spellList.scaleX = 500/spellList.image.width;
    spellList.scaleY = 350/spellList.image.height;
    spellList.x = (imgGameBackground.image.width - spellList.image.width*spellList.scaleX)/2;
    spellList.y = (imgGameBackground.image.height - spellList.image.height*spellList.scaleY)/3;
    abilityListContainer.addChild(spellList);
    abilityListContainer.visible = false;
	
	var itemList = new createjs.Bitmap(queue.getResult("basicWindow80"));
    itemList.scaleX = 500/spellList.image.width;
    itemList.scaleY = 350/spellList.image.height;
    itemList.x = (imgGameBackground.image.width - itemList.image.width*itemList.scaleX)/2;
    itemList.y = (imgGameBackground.image.height - itemList.image.height*itemList.scaleY)/3;
    itemListContainer.addChild(itemList);
    itemListContainer.visible = false;
	
	var levelUp = new createjs.Bitmap(queue.getResult("basicWindow80"));
    levelUp.scaleX = 500/levelUp.image.width;
    levelUp.scaleY = 350/levelUp.image.height;
    levelUp.x = (imgGameBackground.image.width - levelUp.image.width*levelUp.scaleX)/2;
    levelUp.y = (imgGameBackground.image.height - levelUp.image.height*levelUp.scaleY)/3;
    levelUpContainer.addChild(levelUp);
    levelUpContainer.visible = false;
	boss._setupLevelUp();
	
	
	var name = addText(abilityListContainer, "Name", false, null, false, 25);
	var damage = addText(abilityListContainer, "Damage", false, null, false, 25);
	var cost = addText(abilityListContainer, "Cost", false, null, false, 25);
	setToSingleLine([name[0],damage[0],cost[0]], abilityListContainer, null, false, null);
	setToSpacedRow(abilityListContainer, [[name[0]],[damage[0]],[cost[0]]],["center","center","center"]);
	var underscores = addText(abilityListContainer, "------------------------------------------------------------", true, null, false, 25);
   
    var itemName = addText(itemListContainer, "Item", false, null, false, 25);
    var quanitity = addText(itemListContainer, "Quantity", false, null, false, 25);
    setToSingleLine([itemName[0],quanitity[0]], itemListContainer, null, false, null);
	setToSpacedRow(itemListContainer, [[itemName[0]],[quanitity[0]]],["left","right"]);
    var itemsUnderscores = addText(itemListContainer, "------------------------------------------------------------", true, null, false, 25);
    
    boss.addItem(itemsENUM.STEROIDS);
    boss.addItem(itemsENUM.STEROIDS);
    boss.addItem(itemsENUM.HEALTHPOTSMALL);
    boss.addItem(itemsENUM.HEALTHPOTSMALL);
    boss.addItem(itemsENUM.HEALTHPOTSMALL);
    boss.addItem(itemsENUM.HEALTHPOTSMALL);
    boss.addItem(itemsENUM.HEALTHPOTMED);
    boss.addItem(itemsENUM.HEALTHPOTLARGE);
    boss.addItem(itemsENUM.MANAPOTSMALL);
    boss.addItem(itemsENUM.MANAPOTSMALL);
    boss.addItem(itemsENUM.MANAPOTMED);
    boss.addItem(itemsENUM.MANAPOTLARGE);
    
	boss.gold = 50;
	
	var itemBackdrop = new createjs.Bitmap(queue.getResult("itemShop"));
	itemBackdrop.scaleY = 520/itemBackdrop.image.height;
	itemBackdrop.y = 80;
	itemShopContainer.addChild(itemBackdrop);
	var backdrop2 = new createjs.Bitmap(queue.getResult("itemShop"));
	backdrop2.scaleY = 50/backdrop2.image.height;
	backdrop2.y = 545;
	itemShopContainer.addChild(bossGoldContainer);
	bossGoldContainer.addChild(backdrop2);
	var bossGold = new addStatText(boss, "gold", null, 25);
	var bossText = addText(bossGoldContainer, "Gold: ", false, null, false, 25);
	var finished = addText(bossGoldContainer, "Proceed to Next Level", false, function(){itemShopContainer.visible = false; progressHalted = (levelUpContainer.visible); gameContainer.children[0] = levelImages[currentLevel];},true,25);
	setToSpacedRow(bossGoldContainer, [[bossText[0],bossGold.graphic],[finished[0]]],["left","right"]);
	itemShop.initialize();
	
	itemShop.addItem(itemsENUM.STEROIDS);
	itemShop.addItem(itemsENUM.HEALTHPOTSMALL);
	itemShop.addItem(itemsENUM.HEALTHPOTMED);
	itemShop.addItem(itemsENUM.HEALTHPOTLARGE);
	itemShop.addItem(itemsENUM.MANAPOTSMALL);
	itemShop.addItem(itemsENUM.MANAPOTMED);
	itemShop.addItem(itemsENUM.MANAPOTLARGE);
	itemShop.addSpecialItem(itemsENUM.HOLYHANDGRENADE);
	
	gameContainer.addChild(tutorialContainer);
	var tutorialScreen = new createjs.Bitmap(queue.getResult("basicWindow100"));
    tutorialScreen.scaleX = 400/tutorialScreen.image.width;
    tutorialScreen.scaleY = 200/tutorialScreen.image.height;
	tutorialContainer.visible = false;
	tutorialContainer.addChild(tutorialScreen);
	
	
	setupTutorial();
	setupAbilities();
}

function setupTutorial()
{	
	tut = new tutorial();
	var line = new createjs.Shape();
	line.graphics.setStrokeStyle(3);
	line.graphics.beginStroke("#F00");
	line.graphics.moveTo(375, 400);
	line.graphics.lineTo(340, 140);
	line.graphics.endStroke();
	var line2 = new createjs.Shape();
	line2.graphics.setStrokeStyle(3);
	line2.graphics.beginStroke("#F00");
	line2.graphics.moveTo(425, 410);
	line2.graphics.lineTo(500, 400);
	line2.graphics.moveTo(510, 415);
	line2.graphics.lineTo(610, 415);
	line2.graphics.endStroke();
	var line3 = new createjs.Shape();
	line3.graphics.setStrokeStyle(3);
	line3.graphics.beginStroke("#F00");
	line3.graphics.moveTo(375, 350);
	line3.graphics.lineTo(375, 450);
	line3.graphics.moveTo(300, 450);
	line3.graphics.lineTo(450, 450);
	line3.graphics.lineTo(450, 575);
	line3.graphics.lineTo(300, 575);
	line3.graphics.lineTo(300, 450);
	line3.graphics.endStroke();
	var line4 = new createjs.Shape();
	line4.graphics.setStrokeStyle(3);
	line4.graphics.beginStroke("#F00");
	line4.graphics.moveTo(125, 350);
	line4.graphics.lineTo(125, 450);
	line4.graphics.moveTo(5, 450);
	line4.graphics.lineTo(305, 450);
	line4.graphics.lineTo(305, 595);
	line4.graphics.lineTo(5, 595);
	line4.graphics.lineTo(5, 450);
	line4.graphics.endStroke();
	gameContainer.addChild(line);
	gameContainer.addChild(line2);
	gameContainer.addChild(line3);
	gameContainer.addChild(line4);
	tut.addSlide(new vec2(250, 200), "Welcome to our game, Final Boss. In this game you play as the boss and try to take down all of the heroes in each stage to become the ultimate final boss.");
	tut.addSlide(new vec2(250, 400), "First you'll notice that you've achieved a level up. You start the game at level five and obtain three allocation points every time you level up. You can spend them on stats, here. This box will pop up automatically every time you level up.", [line]);
	tut.addSlide(new vec2(50, 400), "Once you click \"Finished\" the box will close and the game will proceed as usual. Any unspent points will be kept, however; you cannot spend them on stats until you level up again. Also, each subsequent point placed into a stat will give you less of a stat boost.", [line2]);
	tut.addSlide(new vec2(150, 150), "You have three basic commands listed on the bottom-middle of your screen. Attack lets you choose a single enemy to use a basic attack on. Abilities lets you choose which ability to cast from your current set of abilities.", [line3]);
	tut.addSlide(new vec2(150, 150), "Items allows you to use an item from a list of your currently stocked items. The value in brackets next to each command is the hotkey to execute the respective command. (These commands are really convenient, just saying)", [line3]);
	tut.addSlide(new vec2(25, 150), "Over here we have our usual health and mp shenanigans going on. You'll use mp for the abilities you cast and you'll use health to....ummm....uh...absorb enemy attacks..? Anyway the real element that matters here is your progress bar.", [line4]);
	tut.addSlide(new vec2(25, 150), "Once your progress bar fills up you will complete your designated action. If an action hasn't been chosen the bar will sit at full until you give a command. Enemies are quick and don't waste any time because.....AI... so it is in your best interest to do the same.", [line4]);
	tut.addSlide(new vec2(250, 50), "Certain abilities can apply statuses but the game wouldn't be as fun if I told you all about that so I'll let you figure out as you go along. The first couple of levels won't be too difficult but the enemies will start to outscale you in the later levels, good luck.");
	tut.addSlide(new vec2(250, 50), "That pretty much sums it up. I'll stop rambling and let you start the game now, best of luck.");
	tut.play();
}

function setupAbilities()
{
	var fireballEffect = addLerpParticle(gameContainer, new vec2(boss.graphic.x, boss.graphic.y), new vec2(0,0), "fireball", 5, 200, "fireball", .5, .5, 30);
	var fireball = new abilities(fireballEffect, 20, [statusENUM.BURN], null, 20, boss, null, "Fireball", "Blasts a single enemy with a medium damage fireball of death.", 50);
	allAbilities.push(fireball);
	boss.addAbility(fireball);
	var swordEffect = addLerpParticle(gameContainer, new vec2(boss.graphic.x, boss.graphic.y), new vec2(0,0), "sword", 2.5, null, null, null, null, 0);
	var attackUp = new abilities(swordEffect, 0, [statusENUM.PHYSATKBOOST], null, 45, boss, abilitiesENUM.BUFF, "Enrage", "You become enraged, granting a physical damage boost for a few turns.", 50);
	allAbilities.push(attackUp);
	var boxEffect = new scaleParticle("box", gameContainer, 192);
	var magicWall = new abilities(boxEffect, 0 ,[statusENUM.MAGICDEFBOOST, statusENUM.PHYSDEFBOOST], null, 80, boss, abilitiesENUM.BUFF, "Magic Wall", "Summons a box of arcane magic to protect yourself for five turns.", 200);
	itemShop.addAbility(magicWall);
	itemShop.addAbility(attackUp);
	var rockFall = new addConeEffect(gameContainer, 3, 20, new vec2(550, -10), new vec2(0, 400), 1.25, "rock", 1/4, 80);
	var rockSlide = new abilities(rockFall, 70, null, null, 100, boss, abilitiesENUM.AOE, "Rock Slide", "You hit the ground with enough force to drop rocks on the enemies.....because Science.", 400);
	itemShop.addAbility(rockSlide);
	var coneEffect = new addConeEffect(gameContainer, 5, 30, new vec2(300, boss.graphic.y), new vec2(400, 0), 2, "fireball", 1/60);
	var dragonBreath = new abilities(coneEffect, 100, [statusENUM.BURN], null, 130, boss, abilitiesENUM.AOE, "Dragon's Breath", "Engulfs all of the enemy heroes in flames. It also looks pretty sweet....so there's that too.", 700);
	itemShop.addAbility(dragonBreath);
	var deathEffect = new addConeEffect(gameContainer, 3, 360, new vec2(650, 300), new vec2(150, 0), 1, "death", 1/60);
	var deathSpell = new abilities(deathEffect, 0, null, null, 0, boss, abilitiesENUM.DEATH, "Death", "Summon a cloud of deathly smoke to take down the heroes instantly.",0);
	allAbilities.push(deathSpell);
	var lightningEffect = addLerpParticle(gameContainer, new vec2(boss.graphic.x, boss.graphic.y), new vec2(0,0), "bolt", 7);
	var lightningBolt = new abilities(lightningEffect, 20, [statusENUM.ZAP], null, 30, boss, null, "Lightning Bolt", "NPC SPELL");
	allAbilities.push(lightningBolt);
}

function setupHeroes()
{
	for(i=0; i<party.length; i++)
	{
		partyContainer.removeChild(party[i].graphic);
	}
	setupParty(gameContainer);
	
	for(var i=0; i<party.length; i++)
	{
		var heroText = new addText(heroInfoContainer, party[i].heroClass+ " HP: ", false, null, false, 17, new addStatText(party[i], "hpCurr", "hpMax", 17), 12);
		var timeBar = addProgressBar(heroInfoContainer, 0, i*30, 100, heroText[0].getMeasuredHeight(), 0, party[i].speed*10, party[i].takeTurn);
		setToSingleLine([heroText[0], heroText[1].graphic, timeBar.outline], heroInfoContainer, null, true);
		heroText[1].alignPoint = heroText[1].graphic.getMeasuredWidth()+heroText[1].graphic.x;
	}
}

function nextLevel()
{
	currentLevel += 1;
	if(currentLevel == levelImages.length)
	{
		victoryContainer.visible = true;
		gameContainer.visible = false;
	}
	for(i=1;i<heroInfoContainer.children.length;i++)
	{
		heroInfoContainer.children[i].visible = false;
	}
	if(currentLevel == 4)
	{
		gameContainer.removeChild(boss.graphic);
		boss.graphic = bigBossGraphic;
		new addMovingText(stage, "EVIL FLOWS THROUGH YOU!!!!", new vec2(52, 202), 5, 40, "#000");
		new addMovingText(stage, "EVIL FLOWS THROUGH YOU!!!!", new vec2(50, 200), 5, 40, "#850091");
		new addScreenShake(5, 20);
		gameContainer.addChildAt(boss.graphic, 1);
	}
	cleanup();
	selector.descript.hide();
	var image = heroInfoContainer.children[0];
	heroInfoContainer.removeAllChildren();
	heroInfoContainer.addChild(image);
	itemShopContainer.visible = true;
	progressHalted = true;
	setupHeroes();
	boss.setup();
	if(currentLevel == 1)
	{
		var x = particles.indexOf(tut);
		particles.splice(x, 1);
		var tut2 = new tutorial();
		tut2.addSlide(new vec2(300, 200), "This is the after-level shop. Once a level is completed you can buy any goods that you can afford. Simply click proceed to next level to fight the next round of heroes.");
		tut2.play();
	}
}

function setupButtons()
{
	var play = new createjs.Sprite(buttonSheet);
	makeButton(play, "play", titleContainer, function()
	{
		titleContainer.visible = false;
		gameContainer.visible = true;
	}, new vec2(350, 400));
    
    
    var creditButton = new createjs.Sprite(creditButtonSheet);
    makeButton(creditButton, "credit", titleContainer, function(evt) {
        titleContainer.visible = false;
        creditContainer.visible = true;
    }, new vec2(300, 480));
    
	var mainMenu = new createjs.Sprite(buttonSheet);
	makeButton(mainMenu, "menu", defeatContainer, setupGame, new vec2(600, 400));
	var mainMenu2 = new createjs.Sprite(buttonSheet);
	makeButton(mainMenu2, "menu", victoryContainer, setupGame, new vec2(600, 400)); 
	var mainMenu3 = new createjs.Sprite(buttonSheet);
	makeButton(mainMenu3, "menu", instructionsContainer, function(evt)
	{
		titleContainer.visible = true;
		instructionsContainer.visible = false;
	}, new vec2(675, 200)); 
    
    var mainMenu4 = new createjs.Sprite(buttonSheet);
    makeButton(mainMenu4, "menu", creditContainer, function(evt)
    {
        titleContainer.visible = true;
        creditContainer.visible = false;
    }, new vec2(600, 550));
}

function setupGame()
{
	bossInfoContainer = new createjs.Container();
    menuContainer = new createjs.Container();
    heroInfoContainer = new createjs.Container();
	partyContainer = new createjs.Container();
    abilityListContainer = new createjs.Container();
	particles = [];
	currentLevel = 0;
	
	createContainers();
	titleContainer.visible = true;
	gameContainer.visible = false;
	defeatContainer.visible = false;
	victoryContainer.visible = false;
    creditContainer.visible = false;
    var attack = new menuItem();
    var ability = new menuItem();
    var items = new menuItem();
	boss = new createPlayer();
	boss.initialize(5);
	setupContainers();
	setupHeroes();
	var hpStatText = new addStatText(boss, "hpCurr", "hpMax", 20);
	var mpStatText = new addStatText(boss, "mpCurr", "mpMax", 20);
	var bossHP = new addText(bossInfoContainer, "HP: ", false, null, false, 20, hpStatText, 8); 
	var bossMP = new addText(bossInfoContainer, "MP: ", false, null, false, 20, mpStatText, 8); 
	setToSingleLine([bossHP[0], hpStatText.graphic, bossMP[0], mpStatText.graphic], bossInfoContainer);
	hpStatText.alignPoint = hpStatText.graphic.getMeasuredWidth()+hpStatText.graphic.x;
	mpStatText.alignPoint = mpStatText.graphic.getMeasuredWidth()+mpStatText.graphic.x;
	var progress = new addProgressBar(bossInfoContainer, 0, 0, null, 30, 0, boss.speed*15, boss.takeTurn);
	boss.progressBar = progress;
	
	bigBossGraphic = new createjs.Sprite(bigBossSheet);
	bigBossGraphic.gotoAndPlay("attack");
	bigBossGraphic.regX = 125;
	bigBossGraphic.regY = -bigBossGraphic.spriteSheet._frames[0].rect.height/2;
	bigBossGraphic.x = 100;
	bigBossGraphic.y = 250;
	
	playCheck = !levelUpContainer.visible && !itemShopContainer.visible && !tutorialContainer.visible;
	
    attack.initialize(menuContainer, "[A] Attack", chooseAttack, true, 30);
    ability.initialize(menuContainer, "[S] Abilities", viewAbilityList, true, 30);
    items.initialize(menuContainer, "[D] Items", viewItemList, true, 30);
}



document.onkeydown = handleKeyDown;
document.onkeyup = handleKeyUp;

function loadFiles() {
    queue = new createjs.LoadQueue(true, "assets/");  //files are stored in 'assets' directory
    queue.on("complete", loadComplete, this);  //when loading is done run 'loadComplete()'
    queue.loadManifest(manifest);  //load files listed in 'manifest'
}

var boss;
var bossSheet;
var bigBossSheet;
var mageSheet;

function loadComplete(evt) {
    //Images
    imgInstructions = new createjs.Bitmap(queue.getResult("instructions"));
    imgDescription = new createjs.Bitmap(queue.getResult("description"));
    imgCredits = new createjs.Bitmap(queue.getResult("credits"));
    imgGameBackground = new createjs.Bitmap(queue.getResult("bg1"));
    imgMainMenu = new createjs.Bitmap(queue.getResult("mainMenu"));
    imgVictory = new createjs.Bitmap(queue.getResult("victory"));
    imgDefeat = new createjs.Bitmap(queue.getResult("defeat"));
    imgShop = new createjs.Bitmap(queue.getResult("shop"));
    imgBattleMenu = new createjs.Bitmap(queue.getResult("battle"));
    imgSpellsItems = new createjs.Bitmap(queue.getResult("spellsItems"));
    //Sounds
    soundButtonOver = new createjs.Sound.play(queue.getResult("buttonOver").src);
    soundButtonClicked = new createjs.Sound.play(queue.getResult("buttonPressed").src);
    buttonSheet = new createjs.SpriteSheet({
        images: [queue.getResult("buttons")],
        frames: [[0,0,152,52,0,77,24],[152,0,152,52,0,77,24],[304,0,152,52,0,77,24],[0,52,211,52,0,78,24],[211,52,211,52,0,78,24],[0,104,211,52,0,78,24],[211,104,179,53,0,78,25],[0,157,179,53,0,78,25],[179,157,179,53,0,78,25],[358,157,52,27,0,26,13],[410,157,52,27,0,26,13],[0,210,52,27,0,26,13],[52,210,52,27,0,26,13],[104,210,52,27,0,26,13],[156,210,52,27,0,26,13]],
        animations: {
            playButton: [0,0, "playButton"],
            playHover: [1,1, "playHover"],
            playClick: [2,2, "playClick"],
            instructionButton: [3,3, "instructionButton"],
            instructionHover: [4,4, "instructionHover"],
            instructionClick: [5,5, "instructionClick"],
            menuButton: [6,6, "menuButton"],
            menuHover: [7,7, "menuHover"],
            menuClick: [8,8, "menuClick"],
            muteButton: [9,9, "muteButton"],
            muteHover: [10,10, "muteHover"],
            muteClick: [11,11, "muteClick"],
            unmuteButton: [12,12, "unmuteButton"],
            unmuteHover: [13,13, "unmuteHover"],
            unmuteClick: [14,14, "unmuteClick"]
        }});
    creditButtonSheet = new createjs.SpriteSheet({
        images: [queue.getResult("credbutton")],
        frames: [[0,0,102,36,0,0,0],[0,36,102,36,0,0,0],[0,72,102,36,0,0,0]],
        animations: {
            creditButton: [0,0, "creditButton"],
            creditHover: [1,1, "creditHover"],
            creditClick: [2,2, "creditClick"]
        }});
	bossSheet = new createjs.SpriteSheet({
	images: [queue.getResult("skullSheet")],
        frames: [[0,0,154,185,0,-105,145.15],[154,0,155,186,0,-105,147.15],[309,0,155,187,0,-105,149.15],[464,0,155,187,0,-105,150.15],[619,0,155,187,0,-105,151.15],[774,0,155,187,0,-105,153.15],[0,187,155,194,0,-105,161.15],  [155,187,155,195,0,-105,163.15],[310,187,155,195,0,-105,164.15],[465,187,155,195,0,-105,165.15],[620,187,155,195,0,-105,167.15],[775,187,155,195,0,-105,168.15],[0,382,155,197,0,-105,171.15],[155,382,155,197,0,-105,172.15],[310,382,155,198,0,-105,174.15],[465,382,154,202,0,-106,180.15],[619,382,155,203,0,-105,179.15],[774,382,155,202,0,-105,177.15],[0,585,155,197,0,-105,171.15],[155,585,155,198,0,-105,170.15],[310,585,155,198,0,-105,169.15],[465,585,155,196,0,-105,166.15],[620,585,155,197,0,-105,166.15],[775,585,155,197,0,-105,164.15],[0,783,155,197,0,-105,163.15],[155,783,155,197,0,-105,162.15],[310,783,155,198,0,-105,161.15],[465,783,155,197,0,-105,159.15],[620,783,155,196,0,-105,157.15],[775,783,154,196,0,-105,156.15]],
        animations: {
            attack: [0, 29, "attack", .5]
            }     
        });
	bigBossSheet = new createjs.SpriteSheet({
        images: [queue.getResult("bigBossSheet")],
        frames: [[0,0,372,371,0,7,369.4],[372,0,372,371,0,7,369.4],[744,0,372,371,0,7,369.4],[1116,0,361,365,0,0,363.4],[1477,0,361,366,0,0,364.4],[0,371,361,367,0,0,365.4],[361,371,360,368,0,0,366.4],[721,371,360,369,0,0,367.4],[1081,371,360,369,0,0,367.4],[1441,371,358,372,0,0,370.4],[0,743,358,373,0,0,371.4],[358,743,358,374,0,0,372.4],[716,743,359,374,0,0,372.4],[1075,743,359,374,0,0,372.4],[1434,743,359,374,0,0,372.4],[0,1117,359,417,0,0,415.4],[359,1117,359,417,0,0,415.4],[718,1117,359,417,0,0,415.4],[1077,1117,360,414,0,0,412.4],[1437,1117,360,414,0,0,412.4],[0,1534,360,414,0,0,412.4],[360,1534,358,369,0,0,367.4],[718,1534,358,369,0,0,367.4],[1076,1534,358,369,0,0,367.4],[1434,1534,358,365,0,0,363.4],[0,1948,358,364,0,0,362.4],[358,1948,358,363,0,0,361.4],[716,1948,358,361,0,0,359.4],[1074,1948,358,360,0,0,358.4],[1432,1948,358,359,0,0,357.4]],
        animations: {
            idle: [0, 0, "idle"],
            attack: [0, 29, "attack", .5]
            }     
        });
	mageSheet = new createjs.SpriteSheet({
        images: [queue.getResult("mage")],
        frames: [[0,0,150,150,0,0,151.5],[150,0,150,150,0,0,151.5],[300,0,150,150,0,0,151.5],[450,0,150,150,0,0,151.5],[600,0,150,150,0,0,151.5],[750,0,150,150,0,0,151.5],[0,150,150,150,0,0,151.5],[150,150,150,150,0,0,151.5],[300,150,150,150,0,0,151.5],[450,150,150,150,0,0,151.5],[600,150,150,150,0,0,151.5],[750,150,150,150,0,0,151.5],[0,300,150,150,0,0,151.5],[150,300,150,150,0,0,151.5],[300,300,150,150,0,0,151.5],[450,300,150,150,0,0,151.5],[600,300,150,150,0,0,151.5],[750,300,150,150,0,0,151.5],[0,450,150,150,0,0,151.5],[150,450,150,150,0,0,151.5],[300,450,150,150,0,0,151.5],[450,450,150,150,0,0,151.5],[600,450,150,150,0,0,151.5],[750,450,150,150,0,0,151.5],[0,600,150,150,0,0,151.5],[150,600,150,150,0,0,151.5],[300,600,150,150,0,0,151.5],[450,600,150,150,0,0,151.5],[600,600,150,150,0,0,151.5],[750,600,150,150,0,0,151.5]],
        animations: {
            idle: [0, 0, "idle"],
            attack: [0, 29, "attack", .5]
            }     
        });
	levelImages[0] = new createjs.Bitmap(queue.getResult("bg1"));
	levelImages[1] = new createjs.Bitmap(queue.getResult("bg2"));
	levelImages[2] = new createjs.Bitmap(queue.getResult("bg3"));
	levelImages[3] = new createjs.Bitmap(queue.getResult("bg4"));
	levelImages[4] = new createjs.Bitmap(queue.getResult("bg5"));
	levelImages[5] = new createjs.Bitmap(queue.getResult("bg6"));
	levelImages[6] = new createjs.Bitmap(queue.getResult("bg7"));
	
	soundDie = new createjs.Sound.play(queue.getResult("deathScream").src);
    soundAttack = new createjs.Sound.play(queue.getResult("attackSound").src);
    soundDrinkPotion = new createjs.Sound.play(queue.getResult("drinkPotion").src);
	
    setupGame();
}

function ItemShop()
{
	this.shopItems = [];
	this.shopAbilities = [];
	this.shopTraps = [];
	
	var that = this;

	this.initialize = function()
	{
		var itemText = addText(itemShopContainer, "Items", false, this.showItems, true, 30, null, null, "View available items.");
		var bar = addText(itemShopContainer, "|", false, null, false, 30);
		var abilityText = addText(itemShopContainer, "Abilities", false, this.showAbilities, true, 30, null, null, "View available abilities.");
		setToSingleLine([itemText[0],bar[0],abilityText[0]], itemShopContainer, null, false, null);
		var dashText = addText(itemShopContainer, "----------------------------------------------------------------------------------------------", true, null, false, 25);
	}
	
	this.addItem = function(item)
	{
		this.showItems();
		var tempItem = new createItem();
		tempItem.initialize(item, null);
		var purchase = function()
		{
			if(boss.gold >= tempItem.shopCost)
			{
				boss.gold -= tempItem.shopCost;
				boss.addItem(item);
			}
			else
			{
				new addMovingText(itemShopContainer, "Insufficient Funds...", new vec2(15, 520), 1.5, 25, "#FFD342")
			}
		};
		var itemText = addText(itemShopContainer, tempItem.item, false, null, false, 25);
		var cost = addText(itemShopContainer, "Price: "+tempItem.shopCost, false, null, false, 25);
		setToSpacedRow(itemShopContainer, [[itemText[0]],[cost[0]]], ["center","center"], tempItem.description, null, null, purchase);
		this.shopItems.push(itemText[0]);
		this.shopItems.push(cost[0]);
	}
	
	this.addAbility = function(ability)
	{
		this.showAbilities();
		var purchase = function()
		{
			if(boss.gold >= ability.shopCost)
			{
				boss.gold -= ability.shopCost;
				boss.addAbility(ability);
				that.removeAbility(ability);
			}
			else
			{
				new addMovingText(itemShopContainer, "Insufficient Funds...", new vec2(15, 520), 1.5, 25, "#FFD342")
			}
		};
		var itemText = addText(itemShopContainer, ability.name, false, null, false, 25);
		var abilityDamage = addText(itemShopContainer, "Damage: " +ability.baseDamage, false, null, false, 25);
		var abilityCost = addText(itemShopContainer, "MP Cost: "+ability.cost, false, null, false, 25);
		var cost = addText(itemShopContainer, "Price: "+ability.shopCost, false, null, false, 25);
		var hitBox = setToSpacedRow(itemShopContainer, [[itemText[0]],[abilityDamage[0]],[abilityCost[0]],[cost[0]]], ["center","center","center","center"], ability.descript, null, null, purchase);
		this.shopAbilities.push(itemText[0]);
		this.shopAbilities.push(abilityDamage[0]);
		this.shopAbilities.push(abilityCost[0]);
		this.shopAbilities.push(cost[0]);
		this.shopAbilities.push(hitBox);
	}
	
	this.removeAbility = function(ability)
	{
		for(i=0; i<that.shopAbilities.length;i++)
		{
			if(that.shopAbilities[i].text != undefined && that.shopAbilities[i].text == ability.name)
			{
				removeMenuTextObjects(itemShopContainer, [that.shopAbilities[i],that.shopAbilities[i+1],that.shopAbilities[i+2],that.shopAbilities[i+3],that.shopAbilities[i+4]]);
				return;
			}
		}
	}
	
	this.addSpecialItem = function(item)
	{
		this.showItems();
		var tempItem = new createItem();
		tempItem.initialize(item, null);
		var purchase = function()
		{
			if(boss.gold >= tempItem.shopCost)
			{
				boss.gold -= tempItem.shopCost;
				boss.addItem(item);
				that.removeItem(tempItem);
			}
			else
			{
				new addMovingText(itemShopContainer, "Insufficient Funds...", new vec2(15, 520), 1.5, 25, "#FFD342")
			}
		};
		var itemText = addText(itemShopContainer, tempItem.item, false, null, false, 25);
		var cost = addText(itemShopContainer, "Price: "+tempItem.shopCost, false, null, false, 25);
		setToSpacedRow(itemShopContainer, [[itemText[0]],[cost[0]]], ["center","center"], tempItem.description, null, null, purchase);
		this.shopItems.push(itemText[0]);
		this.shopItems.push(cost[0]);
	}
	
	this.removeItem = function(item)
	{
		removeObjectsInLine(itemShopContainer, item.item);
	}
	
	this.addTrap = function(trap)
	{
		this.showTraps();
		var purchase = function()
		{
			if(boss.gold >= trap.shopCost)
			{
				boss.gold -= trap.shopCost;
				//boss.addAbility(trap);
			}
			else
			{
				new addMovingText(itemShopContainer, "Insufficient Funds...", new vec2(15, 520), 1.5, 25, "#FFD342")
			}
		};
		var itemText = addText(itemShopContainer, trap.name, false, purchase, true, 20);
		var cost = addText(itemShopContainer, trap.shopCost, false, purchase, true, 20);
		setToSpacedRow(itemShopContainer, [[itemText[0]],[cost[0]]], ["left","right"], trap.descript, null, null, purchase);
		this.shopTraps.push(itemText[0]);
		this.shopTraps.push(cost[0]);
	}
	
	this.showItems = function()
	{
		for(i=0; i<that.shopItems.length; i++)
		{
			that.shopItems[i].visible = true;
		}
		for(i=0; i<that.shopAbilities.length; i++)
		{
			that.shopAbilities[i].visible = false;
		}
		for(i=0; i<that.shopTraps.length; i++)
		{
			that.shopTraps[i].visible = false;
		}
	}
	
	this.showAbilities = function()
	{
		for(i=0; i<that.shopItems.length; i++)
		{
			that.shopItems[i].visible = false;
		}
		for(i=0; i<that.shopAbilities.length; i++)
		{
			that.shopAbilities[i].visible = true;
		}
		for(i=0; i<that.shopTraps.length; i++)
		{
			that.shopTraps[i].visible = false;
		}
	}
	
	this.showTraps = function()
	{
		for(i=0; i<that.shopItems.length; i++)
		{
			that.shopItems[i].visible = false;
		}
		for(i=0; i<that.shopAbilities.length; i++)
		{
			that.shopAbilities[i].visible = false;
		}
		for(i=0; i<that.shopTraps.length; i++)
		{
			that.shopTraps[i].visible = true;
		}
	}
}
