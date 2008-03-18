<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtOverEtvsDeltaR/DeltaEtOverEtvsDeltaRCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtOverEtvsDeltaRdET_Score_vs_et", "DeltaEtOverEtvsDeltaR/DeltaEtOverEtvsDeltaRCompare_etBin");
	generate_other_pictures("DeltaEtOverEtvsDeltaRdR_Allbins", "DeltaEtOverEtvsDeltaRSigmaDeltaEtOverEt_vs_DeltaR");
	
?>

</body>
</html>