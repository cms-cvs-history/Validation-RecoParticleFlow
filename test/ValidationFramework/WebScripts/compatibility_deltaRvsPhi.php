<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaRvsPhi/DeltaRvsPhiCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaRvsPhidET_Score_vs_et", "DeltaRvsPhi/DeltaRvsPhiCompare_etBin");
	generate_other_pictures("DeltaRvsPhidPhi_Allbins", "DeltaRvsPhiSigmaDeltaR_vs_Phi");
	
?>

</body>
</html>