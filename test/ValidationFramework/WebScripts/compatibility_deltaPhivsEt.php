<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaPhivsEt/DeltaPhivsEtCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaPhivsEtdET_Score_vs_et", "DeltaPhivsEt/DeltaPhivsEtCompare_etBin");
	generate_other_pictures("DeltaPhivsEtdEt_Allbins", "DeltaPhivsEtSigmaDeltaPhi_vs_Et");
	
?>

</body>
</html>