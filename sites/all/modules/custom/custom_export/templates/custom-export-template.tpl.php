<?php print '<?xml version="1.0" encoding="utf-8" ?>'; ?>

<CARS>
  <?php foreach($items as $item): ?>
  <ITEM>
    <ITEM_ID><?php print $item['item_id']; ?></ITEM_ID>
    <NAME><![CDATA[<?php print $item['name']; ?>]]></NAME>
    <MANUFACTURER><![CDATA[<?php print $item['manufacturer']; ?>]]></MANUFACTURER>
    <CLASS><![CDATA[<?php print $item['class']; ?>]]></CLASS>
    <EQUIPMENT><![CDATA[<?php print $item['equipment']; ?>]]></EQUIPMENT>
    <COLORS>
      <COLOR>
        <ID><?php print $item['color_id']; ?></ID>
        <NAME><![CDATA[<?php print $item['color_name']; ?>]]></NAME>
        <KIND><![CDATA[<?php print $item['color_kind']; ?>]]></KIND>
      </COLOR>
    </COLORS>
    <IMAGES>
      <?php foreach($item['images'] as $image): ?>
        <IMG><?php print $image; ?></IMG>
      <?php endforeach; ?>
    </IMAGES>
    <MODELS>
      <?php foreach($item['models'] as $model): ?>
      <MODEL>
        <TAX_PAYER><?php print $model['tax_payer']; ?></TAX_PAYER>
        <ENGINE><![CDATA[<?php print $model['engine']; ?>]]></ENGINE>
        <FUEL><?php print $model['fuel']; ?></FUEL>
        <VOL><?php print $model['vol']; ?></VOL>
        <AWD><?php print $model['awd']; ?></AWD>
        <POWER><?php print $model['power']; ?></POWER>
        <BODY><?php print $model['body']; ?></BODY>
        <TRANSMISSION><?php print $model['transmission']; ?></TRANSMISSION>
        <COLOR><?php print $model['color']; ?></COLOR>
        <MONTHS><?php print $model['months']; ?></MONTHS>
        <PER_YEAR><?php print $model['per_year']; ?></PER_YEAR>
        <FREE_PER_YEAR><?php print $model['free_per_year']; ?></FREE_PER_YEAR>
        <PNEU><?php print $model['pneu']; ?></PNEU>
        <INSURANCE><?php print $model['insurance']; ?></INSURANCE>
        <STAMP><?php print $model['stamp']; ?></STAMP>
        <RADIO><?php print $model['radio']; ?></RADIO>
        <SERVICE><?php print $model['service']; ?></SERVICE>
        <ROAD_TAX><?php print $model['road_tax']; ?></ROAD_TAX>
        <LEASING_PARTNER><![CDATA[<?php print $model['leasing_partner']; ?>]]></LEASING_PARTNER>
        <PRICE><?php print $model['price']; ?></PRICE>
        <PRICE_VAT><?php print $model['price_vat']; ?></PRICE_VAT>
        <STORAGE><?php print $model['storage']; ?></STORAGE>
        <URL><![CDATA[<?php print $model['url']; ?>]]></URL>
      </MODEL>
      <?php endforeach; ?>
    </MODELS>
  </ITEM>
  <?php endforeach; ?>
</CARS>
