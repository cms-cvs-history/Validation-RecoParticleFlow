<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaEtOverEtvsEt/DeltaEtOverEtvsEtCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaEtOverEtvsEtdET_Score_vs_et", "DeltaEtOverEtvsEt/DeltaEtOverEtvsEtCompare_etBin");
	generate_other_pictures("DeltaEtOverEtvsEtdEt_Allbins", "DeltaEtOverEtvsEtSigmaDeltaEtOverEt_vs_Et");
	
?>

</body>
</html>