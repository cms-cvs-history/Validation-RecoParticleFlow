<? 
function generate_javascript($picture_path)
{
	echo "function tn_l(bin)\n";
	echo "{\n";
    echo "  clear_r()\n";
    echo "  document.getElementById('thumblink_l').href = '".$picture_path."' + bin + '.gif'\n";
    echo "  document.getElementById('thumb_l').src = '".$picture_path."' + bin + '.gif'\n";
    echo "  document.getElementById('thumb_l').width = '250'\n";
    echo "  document.getElementById('thumb_l').height = '200'\n";
    echo "  document.getElementById('thumb_l').border = '1'\n";
    echo "}\n";
	echo "\n";
    echo "function tn_r(bin) {\n";
    echo "  clear_l()\n";
    echo "  document.getElementById('thumblink_r').href = '".$picture_path."' + bin + '.gif'\n";
    echo "  document.getElementById('thumb_r').src ='".$picture_path."' + bin + '.gif'\n";
    echo "  document.getElementById('thumb_r').width = '250'\n";
    echo "  document.getElementById('thumb_r').height = '200'\n";
    echo "  document.getElementById('thumb_r').border = '1'\n";
   echo " }\n";
	echo "\n";
    echo "function clear_l() {\n";
    echo "  document.getElementById('thumblink_l').href = '#'\n";
    echo "  document.getElementById('thumb_l').src = ''\n";
    echo "  document.getElementById('thumb_l').width = '0'\n";
    echo "  document.getElementById('thumb_l').height = '0'\n";
    echo "  document.getElementById('thumb_l').border = '0'\n";
    echo "}\n";
	echo "\n";
   echo " function clear_r() {\n";
    echo "  document.getElementById('thumblink_r').href = '#'\n";
    echo "  document.getElementById('thumb_r').src = ''\n";
    echo "  document.getElementById('thumb_r').width = '0'\n";
    echo "  document.getElementById('thumb_r').height = '0'\n";
    echo "  document.getElementById('thumb_r').border = '0'\n";
    echo "}\n";
	echo "\n";
    echo "function clear_all() {\n";
    echo "  clear_l()\n";
    echo "  clear_r()\n";
    echo "}\n";
	echo "\n";
}



function generate_map($picture_path_score,$picture_path)
{
	
	
	echo "<div id='main_d'>";
	echo "<img src=".$picture_path_score.".gif usemap='#results' alt='' style='border-style: none;'>";
	echo "<map id='#results' name='results' onMouseOut='Clear_all()'>";



	$xpos=159.5;
	$ypos=164.757;
	for($i=1;$i<=100;$i++)
	{
		echo "<area shape=rect coords=".($xpos+($i-1)*7.36).",410,".($ypos+($i-1)*7.36).",39\n";
 		if($i<10)
 		{
 			echo "href=".$picture_path."000".$i.".gif\n";
 			echo "onMouseOver=tn_r('000".$i."')>\n";
 		}
 		else if($i<100)
 		{
 			echo "href=".$picture_path."00".$i.".gif\n";
 			echo "onMouseOver=tn_r('00".$i."')>\n";
 		}
	}

 
	echo "</map>";
	echo "</div>";
	echo "<div id='thumb_dl'><a href='#' id='thumblink_l'><img src='' id='thumb_l' width=0 height=0 border=0></a></div>";
	echo "<div id='thumb_dr'><a href='#' id='thumblink_r'><img src='' id='thumb_r' width=0 height=0 border=0></a></div>";
}

function generate_other_pictures($picture_sigma,$picture_allbins)
{
	echo "<div id='All bins'><img src=".$picture_allbins.".gif></div>";
	echo "<div id='sigma'><img src=".$picture_sigma.".gif></div>";

}

?>