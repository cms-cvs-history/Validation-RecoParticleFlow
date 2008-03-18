<? include 'compatibility_base.php'; ?>

<html>

<head>
  <title>Compatibility vs eta-ring</title>
  <meta content="Thomas Punz & Ronald Remington" name="author">
  <script type="text/javascript">
		<? generate_javascript("DeltaPhiOverPhivsEt/DeltaPhiOverPhivsEtCompare_etBin"); ?>
  </script>
</head>

<body>

<style type="text/css">
	@import url("stylesheet.css");
</style>

<? 

	generate_map("DeltaPhiOverPhivsEtdET_Score_vs_et", "DeltaPhiOverPhivsEt/DeltaPhiOverPhivsEtCompare_etBin");
	generate_other_pictures("DeltaPhiOverPhivsEtdEt_Allbins", "DeltaPhiOverPhivsEtSigmaDeltaPhiOverPhi_vs_Et");
	
?>

</body>
</html>