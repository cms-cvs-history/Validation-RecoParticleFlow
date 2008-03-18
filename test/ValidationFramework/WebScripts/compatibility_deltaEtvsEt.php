<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtvsEt/DeltaEtvsEtCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtvsEtdET_Score_vs_et", "DeltaEtvsEt/DeltaEtvsEtCompare_etBin");
	generate_other_pictures("DeltaEtvsEtdEt_Allbins", "DeltaEtvsEtSigmaDeltaEt_vs_Et");
	
?>

</body>
</html>