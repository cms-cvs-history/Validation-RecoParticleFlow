<html>
<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remmington" name="author">
  <script type="text/javascript">

    function tn_l(bin) {
      clear_r()
      document.getElementById("thumblink_l").href = "DeltaPhivsPhi/DeltaPhivsPhiCompare_etBin" + bin + ".gif"
      document.getElementById("thumb_l").src = "DeltaPhivsPhi/DeltaPhivsPhiCompare_etBin" + bin + ".gif"
      document.getElementById("thumb_l").width = "250"
      document.getElementById("thumb_l").height = "200"
      document.getElementById("thumb_l").border = "1"
    }

    function tn_r(bin) {
      clear_l()
      document.getElementById("thumblink_r").href = "DeltaPhivsPhi/DeltaPhivsPhiCompare_etBin" + bin + ".gif"
      document.getElementById("thumb_r").src = "DeltaPhivsPhi/DeltaPhivsPhiCompare_etBin" + bin + ".gif"
      document.getElementById("thumb_r").width = "250"
      document.getElementById("thumb_r").height = "200"
      document.getElementById("thumb_r").border = "1"
    }

    function clear_l() {
      document.getElementById("thumblink_l").href = "#"
      document.getElementById("thumb_l").src = ""
      document.getElementById("thumb_l").width = "0"
      document.getElementById("thumb_l").height = "0"
      document.getElementById("thumb_l").border = "0"
    }

    function clear_r() {
      document.getElementById("thumblink_r").href = "#"
      document.getElementById("thumb_r").src = "" 
      document.getElementById("thumb_r").width = "0"
      document.getElementById("thumb_r").height = "0"
      document.getElementById("thumb_r").border = "0"
    }

    function clear_all() {
      clear_l()
      clear_r()
    }

  </script>
</head>
<body>
<style type="text/css">
#thumb_dl {position: absolute; position: fixed; left: 220px; top: 80px; text-align: center;}
#thumb_dr {position: absolute; position: fixed; left: 600px; top: 80px; text-align: center;}

</style>
<!-- added for IE compatibility
<script language="JScript">
if (document.recalc && document.body.attachEvent) {
  theDiv.style.setExpression("top", "document.body.scrollTop + 150");
  document.body.onscroll = function() { document.recalc(true) };
}
</script> -->
<!-- <div style="text-align: center;"><img src="Results_vs_etaRing.gif" usemap="#Results_vs_etaRing" alt="" style="border-style: none; width: 996px; height: 472px;"> -->
<div id="main_d">
<img src="DeltaPhivsPhidET_Score_vs_et.gif" usemap="#results" alt="" style="border-style: none;">
<map id="#results" name="results" onMouseOut="Clear_all()">

<?

	$xpos=159.5;
	$ypos=164.757;
	for($i=1;$i<=100;$i++)
	{
		echo "<area shape=rect coords=".($xpos+($i-1)*7.36).",410,".($ypos+($i-1)*7.36).",39\n";
 		if($i<10)
 		{
 			echo "href=DeltaPhivsPhi/DeltaPhivsPhiCompare_etBin000".$i.".gif\n";
 			echo "onMouseOver=tn_r('000".$i."')>\n";
 		}
 		else if($i<100)
 		{
 			echo "href=DeltaPhivsPhi/DeltaPhivsPhiCompare_etBin00".$i.".gif\n";
 			echo "onMouseOver=tn_r('00".$i."')>\n";
 		}
	}
?>
 
  </map>
</div>

<div id="All bins"><img src=DeltaPhivsPhidEt_Allbins.gif></div>
<div id="sigma"><img src=DeltaPhivsPhiSigmaEtOverEt_vs_et.gif></div>
<div id="thumb_dl"><a href="#" id="thumblink_l"><img src="" id="thumb_l" width=0 height=0 border=0></a></div>
<div id="thumb_dr"><a href="#" id="thumblink_r"><img src="" id="thumb_r" width=0 height=0 border=0></a></div>
</body>
</html>