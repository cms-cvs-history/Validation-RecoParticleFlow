<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtvsPhi/DeltaEtvsPhiCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtvsPhidET_Score_vs_et", "DeltaEtvsPhi/DeltaEtvsPhiCompare_etBin");
	generate_other_pictures("DeltaEtvsPhidPhi_Allbins", "DeltaEtvsPhiSigmaDeltaEt_vs_Phi");
	
?>

</body>
</html>