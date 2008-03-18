<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaPhivsPhi/DeltaPhivsPhiCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaPhivsPhidET_Score_vs_et", "DeltaEtvsDeltaR/DeltaPhivsPhiCompare_etBin");
	generate_other_pictures("DeltaPhivsPhidPhi_Allbins", "DeltaPhivsPhiSigmaDeltaPhi_vs_Phi");
	
?>

</body>
</html>