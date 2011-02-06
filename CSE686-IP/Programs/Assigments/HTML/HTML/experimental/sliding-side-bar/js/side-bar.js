var isExtended = 0;
var height = 450;
var width = 200;
var slideDuration = 1000;
var opacityDuration = 1500;

function extendContract(){
	
	if(isExtended == 0){
		
		sideBarSlide(0, height, 0, width);
		
		sideBarOpacity(0, 1);
	
		isExtended = 1;
		
		// make expand tab arrow image face left (inwards)
		$('sideBarTab').childNodes[0].src = $('sideBarTab').childNodes[0].src.replace(/(\.[^.]+)$/, '-active$1');
		
	}
	else{
		
		sideBarSlide(height, 0, width, 0);
		
		sideBarOpacity(1, 0);
		
		isExtended = 0;
		
		// make expand tab arrow image face right (outwards)
		
		$('sideBarTab').childNodes[0].src = $('sideBarTab').childNodes[0].src.replace(/-active(\.[^.]+)$/, '$1');
	}

}

function sideBarSlide(fromHeight, toHeight, fromWidth, toWidth){
		var myEffects = new Fx.Styles('sideBarContents', {duration: slideDuration, transition: Fx.Transitions.linear});
		myEffects.custom({
			 'height': [fromHeight, toHeight],
			 'width': [fromWidth, toWidth]
		});
}

function sideBarOpacity(from, to){
		var myEffects = new Fx.Styles('sideBarContents', {duration: opacityDuration, transition: Fx.Transitions.linear});
		myEffects.custom({
			 'opacity': [from, to]
		});
}

function init(){
	$('sideBarTab').addEvent('click', function(){extendContract()});
}

window.addEvent('load', function(){init()});