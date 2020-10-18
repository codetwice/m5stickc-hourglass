<?php
	$infiles = [];
	for ($i=1; $i<$argc; $i++) {
		$infiles[] = $argv[$i];
	}
	
	$colorMap = [];
	
	function parseColor($color) {
		$r = $color >> 16 & 0xff;
		$g = $color >> 8 & 0xff;
		$b = $color & 0xff;
		return [ $r, $g, $b ];
	}
		
	function rgb24to16($color) {
		$r = $color >> 16 & 0xff;
		$g = $color >> 8 & 0xff;
		$b = $color & 0xff;
		$rgb565 = ($r & 0b11111000) << 8 | ($g & 0b11111100) << 3 | $b >> 3;		
		if ($color == 10852492) {
			printf("r:%d, g:%d, b:%d\r\n", $r, $g, $b);
			printf("int: %d\r\n", $rgb565);
			printf("hex: %x\r\n", $rgb565);
			die();
		}
		return $rgb565;
	}

	function generateImageData($filename) {
		global $colorMap;
		$img = imagecreatefrompng($filename);
		$width = imagesx($img);
		$height = imagesy($img);
		$imageString = "";
		$imageString .= sprintf("%s (%dx%d):\r\n", $filename, $width, $height);
		$imageString .= "{";

		for ($y = 0; $y < $height; $y++) {
			$imageString .= sprintf("\r\n");
			for ($x = 0; $x < $width; $x++) {
				$color = imagecolorat($img, $x, $y);
				if (!isset($colorMap[$color])) {
					$colorIndex = count($colorMap);
					$colorMap[$color] = $colorIndex;
				}
			
				$colorIndex = $colorMap[$color];					
				$imageString .= sprintf("0x%X, ", rgb24to16($color));
				
			}
		}
	
		$imageString .= "\r\n}\r\n";
		imagedestroy($img);
		return $imageString;
	}
	
	function generatePalette() {
		global $colorMap;
		$colorString = "static PALETTE_ENTRY palette[] = {\r\n";
		foreach ($colorMap as $color => $index) {
			$rgb = parseColor($color);
			$colorString .= sprintf("\t(PALETTE_ENTRY) { %d, %d, %d, 0 }, \r\n", $rgb[0], $rgb[1], $rgb[2]);
		}

		$colorString .= "}\r\n";
		return $colorString;
	}
	
	foreach ($infiles as $infile) {
		echo generateImageData($infile);
	}
	
	printf("Color map:\r\n");
	echo generatePalette();
		
?>