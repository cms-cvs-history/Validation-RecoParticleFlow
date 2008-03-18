<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaRvsEt/DeltaRvsEtCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaRvsEtdET_Score_vs_et", "DeltaRvsEt/DeltaRvsEtCompare_etBin");
	generate_other_pictures("DeltaRvsEtdEt_Allbins", "DeltaRvsEtSigmaDeltaR_vs_Et");
	
?>

</body>
</html>