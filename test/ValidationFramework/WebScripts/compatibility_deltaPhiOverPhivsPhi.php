<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaPhiOverPhivsPhi/DeltaPhiOverPhivsPhiCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaPhiOverPhivsPhidET_Score_vs_et", "DeltaPhiOverPhivsPhi/DeltaPhiOverPhivsPhiCompare_etBin");
	generate_other_pictures("DeltaPhiOverPhivsPhidPhi_Allbins", "DeltaPhiOverPhivsPhiSigmaDeltaPhiOverPhi_vs_Phi");
	
?>

</body>
</html>