<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtvsDeltaR/DeltaEtvsDeltaRCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtvsDeltaRdET_Score_vs_et", "DeltaEtvsDeltaR/DeltaEtvsDeltaRCompare_etBin");
	generate_other_pictures("DeltaEtvsDeltaRdR_Allbins", "DeltaEtvsDeltaRSigmaDeltaEt_vs_DeltaR");
	
?>

</body>
</html>